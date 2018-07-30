#pragma region system include
#include <string>
#pragma endregion

#pragma region project include
#include "World.h"
#include "Macro.h"
#include "Engine.h"
#include "ContentManagement.h"
#include "Player.h"
#include "Enemy.h"
#pragma endregion

#pragma region using
using namespace std;
#pragma endregion

#pragma region public function
// initialize world
void GWorld::Init()
{
	// string to define world
	string world;

	// add lines to world string
	// string 100x20
	// 1 block is 64 x 64 pixel
	// screen has 20 (width) and 12 (height) blocks
	// X = dirt (outside)
	// 0 = black (free, background)
	// W = way (walk on)
	// L = lava (death)
	// S = start point of player
	// E = start point of Enemy
	world += "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
	world += "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
	world += "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
	world += "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
	world += "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB\n";
	world += "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
	world += "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n";
	world += "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
	world += "WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW\n";
	world += "LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
	world += "LLLLLLLLSLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL\n";
	world += "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX\n";


	// width and height of world
	int width = 0, height = 1;

	// through world string
	for (int i = 0; i < world.length(); i++)
	{
		// increase width
		width++;

		// if end of line increase height and reset width
		if (world[i] == '\n')
		{
			height++;
			width = 0;
			continue;
		}

		// create textured object
		CTexturedObject* pObj = new CTexturedObject(
			SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT),
			SVector2(WORLD_BLOCK_WIDTH, WORLD_BLOCK_HEIGHT),
			CEngine::Get()->GetRenderer(),
			"Texture/World/Background_Layer1.png"

		);


		// x position of texture in atlas map
		int xPosOfTexture = 0;

		// switch char in world string
		switch (world[i])
		{
		// if dirt set position of texture in atlas map
		case 'X':
		{
			xPosOfTexture = WORLD_BLOCK_ATLAS_WIDTH;

			// set collision type to wall
			pObj->SetColType(ECollisionType::WALL);
			break;
		}

		// if way set position of texture in atlas map
		case 'W':
		{
			xPosOfTexture = 6 * WORLD_BLOCK_ATLAS_WIDTH;
			
			// set collision type to wall
			pObj->SetColType(ECollisionType::NONE);
			break;
		}

		// if lava set position of texture in atlas map
		case 'L':
		{
			xPosOfTexture = 2 * WORLD_BLOCK_ATLAS_WIDTH;
			
			// set collision type to wall
			pObj->SetColType(ECollisionType::NONE);
			break;
		}
		case 'A':
		{
			xPosOfTexture = 5 * WORLD_BLOCK_ATLAS_WIDTH;

			// set collision type to wall
			pObj->SetColType(ECollisionType::NONE);
			break;
		}

		// if lava set position of texture in atlas map
		case 'B':
		{
			xPosOfTexture = 4 * WORLD_BLOCK_ATLAS_WIDTH;

			// set collision type to wall
			pObj->SetColType(ECollisionType::NONE);
			break;
		}

		case 'S':
		{
			// create textured object
			GPlayer * pPlayer = new GPlayer(
				SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT - PLAYER_HEIGHT), 
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				CEngine::Get()->GetRenderer(), 
				"Texture/Character/Player/Hunter_standing.png");

			// set player values
			pPlayer->SetSpeed(PLAYER_SPEED);
			pPlayer->SetMirror(PLAYER_MIRROR);
			pPlayer->SetColType(ECollisionType::MOVE);
			pPlayer->ActivateGravity();

			// add player to persistant list
			CEngine::Get()->GetCM()->AddPersistantObject(pPlayer);
			break;
		}

		case 'E':
		{
			// create textured object
			GEnemy * pEnemy = new GEnemy(
				SVector2((width - 1) * WORLD_BLOCK_WIDTH, (height - 1) * WORLD_BLOCK_HEIGHT - PLAYER_HEIGHT),
				SVector2(PLAYER_WIDTH, PLAYER_HEIGHT),
				CEngine::Get()->GetRenderer(),
				"Texture/Character/Player/Enemy_Skelett.png");

			// set player values
			pEnemy->SetSpeed(ENEMY_SPEED);
			pEnemy->SetMirror(ENEMY_MIRROR);
			pEnemy->SetColType(ECollisionType::MOVE);
			pEnemy->ActivateGravity();

			// add player to persistant list
			CEngine::Get()->GetCM()->AddSceneObject(pEnemy);
			break;
		}

		default:
			break;
		}

		// set source rect of object
		pObj->SetSrcRect(SRect(xPosOfTexture, 0, WORLD_BLOCK_ATLAS_WIDTH, WORLD_BLOCK_ATLAS_HEIGHT));

		// add object to scene list
		CEngine::Get()->GetCM()->AddSceneObject(pObj);
	}
}
#pragma endregion