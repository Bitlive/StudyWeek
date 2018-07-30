#include <iostream>	///TODO: DELETE
#include <string>	///TODO: DELETE
#include <vector>

#pragma region project include
#include "Player.h"
#include "Input.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Physic.h"
#include "Renderer.h"
#include "Time.h"
#include "Vector2.h" ///TODO: DELETE
#include "Bullet.h"
#include "World.h"
#pragma endregion

#pragma region public override function
// update every frame
void GPlayer::Update(float _deltaTime)
{
	
	if(SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		// create textured object
		GBullet * pBullet = new GBullet(
			m_position,
			SVector2(BULLET_WIDTH, BULLET_HEIGHT),
			CEngine::Get()->GetRenderer(),
			"Texture/Character/Player/T_Samus_Idle.png");

		pBullet->SetSpeed(BULLET_SPEED);
		pBullet->SetColType(ECollisionType::NONE);

		// add player to persistant list
		CEngine::Get()->GetCM()->AddSceneObject(pBullet);
		
	

	}

	// movement left
	if (CInput::GetKey(SDL_SCANCODE_A))
	{
		// set movement and mirror
		m_movement.X = -1.0f;
		m_mirror.X = 1.0f;
	}

	// movement right
	else if (CInput::GetKey(SDL_SCANCODE_D))
	{
		// set movemenet and mirror
		m_movement.X = 1.0f;
		m_mirror.X = 0.0f;
	}

	// no movement left or right
	else
		m_movement.X = 0.0f;

	// if key space is pressed this frame and jump not active and grounded
	if (CInput::GetKeyDown(SDL_SCANCODE_SPACE) && !m_jump && m_grounded)
	{
		// set jump enable, gravity false and set jump time
		m_jump = true;
		m_jumpTime = PLAYER_JUMP_TIME;
		m_gravity = false;
	}

	// update parent
	CMoveObject::Update(_deltaTime);

	// if jump enabled
	if(m_jump)
	{
		// decrease jump time
		m_jumpTime -= _deltaTime;

		// if jump time under 0
		if (m_jumpTime <= 0.0f)
		{
			// deactivate jump and activate gravity
			m_jump = false;
			m_gravity = true;
		}

		// moveable default true
		bool moveable = true;

		// next position
		SVector2 nextPos = m_position;
		nextPos.Y -= PLAYER_JUMP_FORCE * _deltaTime;

		// next rect
		SRect nextRect = m_rect;
		nextRect.x = nextPos.X;
		nextRect.y = nextPos.Y;

		// through all scene objects
		for (CObject* pObj : CEngine::Get()->GetCM()->GetSceneObjects())
		{
			// if current object is self continue
			if ((CMoveObject*)pObj && pObj == this)
				continue;

			// if collision type none
			if (((CTexturedObject*)pObj)->GetColType() == ECollisionType::NONE)
				continue;

			// set moveable by checking collision
			moveable = !CPhysic::RectRectCollision(nextRect, ((CTexturedObject*)pObj)->GetRect());

			// if not moveable cancel collision check
			if (!moveable)
				break;
		}

		// if moveable
		if (moveable)
		{
			// through all persistant objects
			for (CObject* pObj : CEngine::Get()->GetCM()->GetPersistantObjects())
			{
				// if current object is self continue
				if ((CMoveObject*)pObj && pObj == this)
					continue;

				// if collision type none
				if (((CTexturedObject*)pObj)->GetColType() == ECollisionType::NONE)
					continue;

				// set moveable by checking collision
				moveable = !CPhysic::RectRectCollision(nextRect, ((CTexturedObject*)pObj)->GetRect());

				// if not moveable cancel collision check
				if (!moveable)
					break;
			}
		}

		// if still moveable set y position
		if (moveable)
		{
			m_position.Y -= PLAYER_JUMP_FORCE * _deltaTime;
			m_rect.y = m_position.Y;
		}
	}

	// set position of camera
	CEngine::Get()->GetRenderer()->SetCamera(
		SVector2(m_position.X + PLAYER_WIDTH / 2, m_position.Y + PLAYER_HEIGHT / 2)
	);

	/// <summary>
	/// TODO: DELETE
	/// </summary>
	// print player position
	std::string s = "Position Y: ";
	s += std::to_string(m_position.Y);
	LOG_ERROR("", s.c_str());
}

// render every frame
void GPlayer::Render(CRenderer * _pRenderer)
{
	CMoveObject::Render(_pRenderer);
}
#pragma endregion