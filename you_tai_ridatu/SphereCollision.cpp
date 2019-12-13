#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"
#include "Model.h"
#include"SphereCollision.h"
#include"Enemy.h"
#include"character.h"
#include"wall.h"
#include"bullet.h"
#include "exp.h"
#include"shadow.h"
#include"Dummy.h"
#include"Coa.h"
#include"fade.h"
#include"scene.h"
#include"HUD.h"
#include"billboard.h"

bool Hit_flag = false;
bool Hit_Wall_Enemy = false;
int Enemy = 0;
int Coa = 0;
bool g_bEnd = false;


bool HitSphereCollision(const SphereCollision* pA, const SphereCollision* pB)
{
	return (pA->radius + pB->radius)*(pA->radius + pB->radius)>D3DXVec3LengthSq(&(pA->CenterPosition-pB->CenterPosition));
}

void AtariHantei_Enemy(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{

		//ENEMY
		if (!Enemy_IsEnable(i))
		{
			continue;
		}

		if (HitSphereCollision(Chara_GetCollision(), Enemy_GetCollision(i)))
		{
			Enemy_Destroy(i);
			Exp_Create(Enemy_GetPos(i).x, Enemy_GetPos(i).y + 2.0f, Enemy_GetPos(i).z);
			Enemy++;
		}
		for (int j = 0; j < WALL_MAX; j++)
		{
			if (!Wall_IsEnable(j))
			{
				continue;
			}
			if (HitSphereCollision(Enemy_GetCollision(i), Wall_GetCollision(j)))
			{
				Wall_Hit_Enemy(i, Hit_Wall_Enemy);
			}
		}
	}

	
}

void AtariHantei_Wall(void)
{
	for (int j = 0; j < WALL_MAX; j++)
	{
		//WALL
		if (!Wall_IsEnable(j))
		{
			continue;
		}

		if (HitSphereCollision(Chara_GetCollision(), Wall_GetCollision(j)))
		{
			Hit_flag = true;
			Wall_Hit_Frag(Hit_flag);
			
			break;
		}

		else if (!HitSphereCollision(Chara_GetCollision(), Wall_GetCollision(j)))
		{
			Hit_flag = false;
			Wall_Hit_Frag(Hit_flag);
			
		}
		
	}
}

void AtariHantei_Gost(int Case)
{
	for (int i = 0; i < COA_MAX; i++)
	{

		//COA
		if (!Coa_IsEnable(i))
		{
			continue;
		}
		if (Case == 1)
		{
			if (HitSphereCollision(Dummy_GetCollision(), Coa_GetCollision(i)))
			{
				Coa_Destroy(i);
				Coa++;
				
			}
		}
	}
}

void Scene_Change(void)
{
	if (Enemy >= ENEMY_MAX&&Coa >= COA_MAX)
	{
		scene_Change(SCENE_INDEX_Result);
		Enemy = 0;
		Coa = 0;
		Character_Init();
	}
}

int Get_Enemy_Num(void)
{
	return Enemy;
}

int Get_Coa_Num(void)
{
	return Coa;
}