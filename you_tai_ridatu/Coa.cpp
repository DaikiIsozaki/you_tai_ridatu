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
#include"wall_factory.h"
#include"character.h"
#include"HUD.h"
#include"shadow.h"
#include"Coa.h"

#define HIT_RADIUS		(1.0f)	

typedef struct COA_Tag
{
	SphereCollision Collision;
	D3DXVECTOR3 Pos;
	int type;
	bool flag;	//trueの時に表示
	
	
}COA;

COA Coa[COA_MAX];

bool Draw_flag;

void Coa_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_ENEMY_COA);

	for (int i = 0; i < COA_MAX; i++)
	{
		Coa[i].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Coa[i].Collision.CenterPosition= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Coa[i].Collision.radius = HIT_RADIUS;
		Coa[i].type = 0;
		Coa[i].flag = false;
		Draw_flag = false;
		

	}
}

void Coa_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_ENEMY_COA);
}

void Coa_Update(int Case)
{
	for (int i = 0; i < COA_MAX; i++)
	{
		if (Case == 1)
		{
			Draw_flag = true;
		}
		if(Case==0||Case==2)
		{
			Draw_flag = false;
		}

		Coa[i].Collision.CenterPosition = Coa[i].Pos;
		Coa[i].Collision.radius = HIT_RADIUS;
	}
}

void Coa_Draw(void)
{
	for (int i = 0; i < COA_MAX; i++)
	{
		if (Draw_flag)
		{
			if (Coa[i].flag)
			{
				//もでる
				D3DXMATRIX mtxWorldModel;
				D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
				D3DXMATRIX mtxTranslationModel;
				D3DXMatrixTranslation(&mtxTranslationModel, Coa[i].Pos.x, Coa[i].Pos.y, Coa[i].Pos.z);
				D3DXMATRIX mtxScaringModel;
				D3DXMatrixScaling(&mtxScaringModel, 1.0f, 1.0f, 1.0f);

				mtxWorldModel = mtxScaringModel* mtxTranslationModel;

				Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
				Model_Draw(INDEX_MODEL_ENEMY_COA);
			}
		}
	}
}

void Coa_Create(float x, float y, float z)
{
	for (int i = 0; i < COA_MAX; i++)
	{
		if (!Coa[i].flag)
		{
			Coa[i].flag = true;
			Coa[i].Pos = D3DXVECTOR3(x, y, z);
			break;
		}
	}
}

void Coa_Destroy(int index)
{
	Coa[index].flag = false;
}

bool Coa_IsEnable(int index)
{
	return Coa[index].flag;
}

const SphereCollision* Coa_GetCollision(int index)
{
	return &Coa[index].Collision;
}