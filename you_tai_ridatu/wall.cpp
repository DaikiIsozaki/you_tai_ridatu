#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"debug_primitive.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"
#include "Model.h"
#include"heri.h"
#include"input.h"
#include"soukousya.h"
#include"bullet.h"
#include"Dummy.h"
#include"wall.h"
#include"character.h"

#define HIT_RADIUS	(2.5f)


typedef struct Wall_tag
{
	SphereCollision Collision;
	D3DXVECTOR3 Pos;
	float Ang;
	bool flag;
	bool Hit_flag;
	int type;
}WALL;



WALL Wall[WALL_MAX];
WALL_POS Wall_Pos[WALL_MAX];

void Wall_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_WALL);
	

	for (int i = 0; i < WALL_MAX; i++)
	{
		Wall[i].Pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
		Wall[i].flag = false;
		Wall[i].Hit_flag = false;
		Wall[i].Ang = 0.0f;
		Wall[i].Collision.CenterPosition = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
		for (int j = 0; j < 4; j++)
		{
			Wall_Pos[i].x = 0.0f;
			Wall_Pos[i].y = 0.0f;
			Wall_Pos[i].z = 0.0f;
		}
		
	}
}
void Wall_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_WALL);
	
}

void Wall_Update(void)
{
	for (int i = 0; i < WALL_MAX; i++)
	{
		Wall[i].Collision.CenterPosition = Wall[i].Pos;
		Wall[i].Collision.radius = HIT_RADIUS;
	}
}

void Wall_Draw(void)
{
	for (int i = 0; i < WALL_MAX; i++)
	{
		if (Wall[i].flag)
		{
			//もでる
			D3DXMATRIX mtxWorldModel;
			D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
			D3DXMATRIX mtxTranslationModel;
			D3DXMatrixTranslation(&mtxTranslationModel, Wall[i].Pos.x, Wall[i].Pos.y, Wall[i].Pos.z);
			
			mtxWorldModel =mtxTranslationModel;

			Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
			Model_Draw(INDEX_MODEL_WALL);
			
		}
	}
}



void Wall_Create(float x, float y, float z, int type)
{
	for (int i = 0; i < WALL_MAX; i++)
	{
		if (Wall[i].flag == false)
		{
			Wall[i].flag = true;
			Wall[i].Pos = D3DXVECTOR3(x, y, z);
			Wall[i].type = type;
			break;
		}
	}

}

bool Wall_IsEnable(int index)
{
	return Wall[index].flag;
}

const SphereCollision* Wall_GetCollision(int index)
{
	return &Wall[index].Collision;
}

D3DXVECTOR3 Get_Wall(int index)
{
	return Wall[index].Pos;
}

void Wall_Hit_Frag(int index,bool flag)
{
	Wall[index].Hit_flag = flag;
}

bool Get_Hit_Frag(int index)
{
	return Wall[index].Hit_flag;
}

WALL_POS Get_Wall_Pos(int index)
{
	return Wall_Pos[index];
}

D3DXVECTOR3 Get_Wall_Center_Pos(int index)
{
	return Wall[index].Collision.CenterPosition;
}

void Wall_Hit(int index,bool Hit_Flag)
{
	Wall[index].Hit_flag = Hit_Flag;
		
}