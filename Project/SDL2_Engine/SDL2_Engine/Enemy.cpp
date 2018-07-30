#include "Enemy.h"
#include "Physic.h"
#include "Engine.h"

void GEnemy::Update(float _deltaTime)
{
	m_movement.X = -1.0f;
	m_mirror.X = 1.0f;



	//Shooting
	//if(SDL_GetMouseState(NULL, NULL) && SDL_BUTTON(SDL_BUTTON_LEFT))
	//{
	//
	//}

	// movement left
	//if (CInput::GetKey(SDL_SCANCODE_A))
	//{
	//	// set movement and mirror
	//	m_movement.X = -1.0f;
	//	m_mirror.X = 1.0f;
	//}
	//
	//// movement right
	//else if (CInput::GetKey(SDL_SCANCODE_D))
	//{
	//	// set movemenet and mirror
	//	m_movement.X = 1.0f;
	//	m_mirror.X = 0.0f;
	//}

	// no movement left or right
	//else
	//	m_movement.X = 0.0f;


	// update parent
	CMoveObject::Update(_deltaTime);
	

}