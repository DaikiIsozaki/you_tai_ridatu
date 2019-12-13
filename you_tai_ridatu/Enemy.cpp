#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"
#include "Model.h"
#include"heri.h"
#include"input.h"
#include"bullet.h"
#include"character.h"
#include"SphereCollision.h"
#include"Enemy.h"
#include"shadow.h"
#include"Enemy.h"



#define HIT_RADIUS	(2.0f)

typedef struct Enemy_tag
{
	SphereCollision Collision;
	D3DXVECTOR3 Enemy;
	D3DXVECTOR3 Keep_Enemy;
	D3DXVECTOR3 E_Front;
	D3DXVECTOR3 E_Right;
	D3DXVECTOR3 E_Up;
	D3DXMATRIX g_Save_MatrixEnemy;
	float Enemy_Ang;
	float Enemy_Ang2;
	bool Wall_Hit;
	bool Enemyflag;
	int type;
	int Shadow_number;
	int turnEnemy;

}ENEMY;




ENEMY Enemy[ENEMY_MAX];

void Enemy_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_TEST);

	Model_Xfile_Load(INDEX_MODEL_ENEMY_HEAD);
	Model_Xfile_Load(INDEX_MODEL_ENEMY_BODY);
	Model_Xfile_Load(INDEX_MODEL_ENEMY_HAND);
	Model_Xfile_Load(INDEX_MODEL_ENEMY_LEG);
	

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		Enemy[i].Enemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Enemy[i].Keep_Enemy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Enemy[i].E_Front= D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		Enemy[i].E_Up= D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Enemy[i].E_Right, &Enemy[i].E_Front, &Enemy[i].E_Up);
		D3DXVec3Normalize(&Enemy[i].E_Right, &Enemy[i].E_Right);
		D3DXVec3Cross(&Enemy[i].E_Up, &Enemy[i].E_Right, &Enemy[i].E_Front);
		D3DXVec3Normalize(&Enemy[i].E_Up, &Enemy[i].E_Up);
		D3DXVec3Normalize(&Enemy[i].E_Front, &Enemy[i].E_Front);
		Enemy[i].Enemy_Ang = 0.0f;
		Enemy[i].Enemy_Ang2 = 0.0f;
		Enemy[i].Collision.CenterPosition= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Enemy[i].Enemyflag = false;
		Enemy[i].type = 0;
		Enemy[i].Shadow_number = 0;
		Enemy[i].Wall_Hit = false;
		Enemy[i].turnEnemy = 0;
	}
	
}

void Enemy_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_TEST);

	Model_Finalise(INDEX_MODEL_ENEMY_HEAD);
	Model_Finalise(INDEX_MODEL_ENEMY_BODY);
	Model_Finalise(INDEX_MODEL_ENEMY_HAND);
	Model_Finalise(INDEX_MODEL_ENEMY_LEG);
	

}

void Enemy_Update(int Case)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//座標確定
		Enemy[i].Collision.CenterPosition = Enemy[i].Enemy;
		
		Enemy[i].Collision.radius = HIT_RADIUS;

		Shadow_Create(&Enemy[i].Enemy.x, &Enemy[i].Enemy.z, 4.0f, 4.0f, &Enemy[i].Shadow_number);
	}
}

void Enemy_Stop(int index)
{

	if (Enemy[index].Wall_Hit)
	{
		Enemy[index].Enemy = Enemy[index].Keep_Enemy;
	}

	else
	{
		Enemy[index].Keep_Enemy = Enemy[index].Enemy;
	}

}

void Enemy_Draw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (Enemy[i].Enemyflag)
		{
			//もでる
			D3DXMATRIX mtxWorldModel;
			D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
			D3DXMATRIX mtxTranslationModel;
			D3DXMatrixTranslation(&mtxTranslationModel, Enemy[i].Enemy.x, Enemy[i].Enemy.y, Enemy[i].Enemy.z);
			D3DXMATRIX mtxRotationModel;
			D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(Enemy[i].Enemy_Ang));
			D3DXMATRIX mtxRotationModel2;
			D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(Enemy[i].turnEnemy));

			mtxWorldModel = mtxRotationModel*mtxRotationModel2* mtxTranslationModel;

			Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
			Model_Draw(INDEX_MODEL_TEST);
			break;


		}
	}
}

void Enemy_body_Draw(void)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		Enemy_Stop(i);
		if (Enemy[i].Enemyflag)
		{
			//もでる
			D3DXMATRIX mtxWorldModel;
			D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
			D3DXMATRIX mtxTranslationModel;
			D3DXMatrixTranslation(&mtxTranslationModel, Enemy[i].Enemy.x, Enemy[i].Enemy.y, Enemy[i].Enemy.z);
			D3DXMATRIX mtxScaringModel;
			D3DXMatrixScaling(&mtxScaringModel, 0.2f, 0.2f, 0.2f);
			D3DXMATRIX mtxRotationModel;
			D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(Enemy[i].Enemy_Ang));
			D3DXMATRIX mtxRotationModel2;
			D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(180));

			mtxWorldModel = mtxScaringModel* mtxRotationModel2*mtxRotationModel*mtxTranslationModel;

			Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
			Model_Draw(INDEX_MODEL_ENEMY_BODY);

			Enemy[i].g_Save_MatrixEnemy = mtxWorldModel;

			Enemy_head_Draw(i);
			Enemy_hand_Draw(i);
			Enemy_leg_Draw(i);
		}

		


	}
}

void Enemy_head_Draw(int index)
{
	
	if (Enemy[index].Enemyflag)
	{
		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
		D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &Enemy[index].g_Save_MatrixEnemy);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_ENEMY_HEAD);
	}
	
}

void Enemy_hand_Draw(int index)
{
	
	if (Enemy[index].Enemyflag)
	{
		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る		
		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, 3.0f, 11.0f, 0.0f);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationX(&mtxRotationModel, D3DXToRadian(Enemy[index].Enemy_Ang2));

		mtxWorldModel = mtxRotationModel*mtxTranslationModel;
		D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &Enemy[index].g_Save_MatrixEnemy);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_ENEMY_HAND);

		//もでる
		D3DXMATRIX mtxWorldModel2;
		D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る		
		D3DXMATRIX mtxTranslationModel2;
		D3DXMatrixTranslation(&mtxTranslationModel2, -3.0f, 11.0f, 0.0f);
		D3DXMATRIX mtxRotationModel2;
		D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(-Enemy[index].Enemy_Ang2));
		mtxWorldModel2 = mtxRotationModel2* mtxTranslationModel2;
		D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &Enemy[index].g_Save_MatrixEnemy);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
		Model_Draw(INDEX_MODEL_ENEMY_HAND);
	}
	
}

void Enemy_leg_Draw(int index)
{
	
	if (Enemy[index].Enemyflag)
	{
		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る		
		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, 1.0f, 5.0f, 0.0f);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationX(&mtxRotationModel, D3DXToRadian(Enemy[index].Enemy_Ang2));
		mtxWorldModel = mtxRotationModel* mtxTranslationModel;
		D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &Enemy[index].g_Save_MatrixEnemy);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_CHARA_LEG);

		//もでる
		D3DXMATRIX mtxWorldModel2;
		D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る		
		D3DXMATRIX mtxTranslationModel2;
		D3DXMatrixTranslation(&mtxTranslationModel2, -1.0f, 5.0f, 0.0f);
		D3DXMATRIX mtxRotationModel2;
		D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(-Enemy[index].Enemy_Ang2));
		mtxWorldModel2 = mtxRotationModel2* mtxTranslationModel2;
		D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &Enemy[index].g_Save_MatrixEnemy);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
		Model_Draw(INDEX_MODEL_CHARA_LEG);
	}
	
}

void Enemy_Create(float x, float y, float z,int type,float Ang)
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (Enemy[i].Enemyflag == false)
		{
			Enemy[i].Enemyflag = true;
			Enemy[i].Enemy.x = x;
			Enemy[i].Enemy.y = y;
			Enemy[i].Enemy.z = z;
			Enemy[i].Enemy_Ang = Ang;
			Enemy[i].type = type;

			break;
		}
	}
}

void Enemy_Destroy(int index)
{
	Enemy[index].Enemyflag=false;
	Shadow_Destroy(Enemy[index].Shadow_number);
}

bool Enemy_IsEnable(int index)
{
	return Enemy[index].Enemyflag;
}

const SphereCollision* Enemy_GetCollision(int index)
{
	return &Enemy[index].Collision;
}

D3DXVECTOR3 Enemy_GetPos(int index)
{
	return Enemy[index].Enemy;
}

void Wall_Hit_Enemy(int index,bool flag)
{
	Enemy[index].Wall_Hit = flag;
}