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
#include"wall.h"

#define DummySPEED	(0.01f)
#define DUMMY_LIMIT	(10.0f)
#define HIT_RADIUS	(1.0f)


D3DXVECTOR3 Dummy;
D3DXVECTOR3 D_Front;
D3DXVECTOR3 D_Right;
D3DXVECTOR3 D_Up;

D3DXVECTOR3 Dummy_Pos;
float DummyAng;
float DummyAng2;

typedef struct Gost_Tag
{
	SphereCollision Collision;
}GOST;

GOST Gost;

void Dummy_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_YUREI);
	
	Dummy = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	D_Front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D_Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&D_Right, &D_Front, &D_Up);
	D3DXVec3Normalize(&D_Right, &D_Right);
	D3DXVec3Cross(&D_Up, &D_Right, &D_Front);
	D3DXVec3Normalize(&D_Up, &D_Up);
	D3DXVec3Normalize(&D_Front, &D_Front);
	DummyAng=0.0f;
	DummyAng2 = 0.0f;
}

void Dummy_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_YUREI);
	
}

void Dummy_Update(int Case)
{
	//移動
	
	if (Keyboard_IsPress(DIK_W))
		{
			D3DXVECTOR3 f(D_Front);
			f.y = 0.0f;
			Dummy += f * DummySPEED;
		}
		if (Keyboard_IsPress(DIK_S))
		{
			D3DXVECTOR3 f(D_Front);
			f.y = 0.0f;
			Dummy -= f * DummySPEED;
		}
		D3DXMATRIX mtxR;
		if (Keyboard_IsPress(DIK_A))
		{

			D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.5f));
			D3DXVec3TransformNormal(&D_Front, &D_Front, &mtxR);
			D3DXVec3TransformNormal(&D_Right, &D_Right, &mtxR);
			D3DXVec3TransformNormal(&D_Up, &D_Up, &mtxR);
			DummyAng -= 0.5f;

		}
		if (Keyboard_IsPress(DIK_D))
		{
			D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.5f));
			D3DXVec3TransformNormal(&D_Front, &D_Front, &mtxR);
			D3DXVec3TransformNormal(&D_Right, &D_Right, &mtxR);
			D3DXVec3TransformNormal(&D_Up, &D_Up, &mtxR);
			DummyAng += 0.5f;
		}
		
	

	if (Case == 1)
	{
		DummyAng2 = Get_Ang();
	}
	if (Case==0||Case == 2)
	{
		Dummy = Get_Chara_Pos();	
	}

	

	if (Dummy.x >FIELD_X)
	{
		Dummy.x = 30.0f;
	}

	if (Dummy.x < -FIELD_X)
	{
		Dummy.x = -30.0f;
	}

	if (Dummy.z > FIELD_Z)
	{
		Dummy.z = 30.0f;
	}

	if (Dummy.z < -FIELD_Z)
	{
		Dummy.z = -30.0f;
	}

	Gost.Collision.CenterPosition = Dummy;
	Gost.Collision.radius=HIT_RADIUS;
	
}

void Dummy_Draw(float x, float y, float z,int Case)
{
	if (Case == 1)
	{
		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, x + Dummy.x, y, z + Dummy.z);
		D3DXMATRIX mtxTranslationModel2;
		D3DXMatrixTranslation(&mtxTranslationModel2, 0.0f, 0.0f, -1.0f);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(DummyAng));
		D3DXMATRIX mtxScalingModel;
		D3DXMatrixScaling(&mtxScalingModel, 0.5f, 0.5f, 0.5f);
		
		mtxWorldModel =mtxScalingModel* mtxTranslationModel2*mtxRotationModel* mtxTranslationModel;

		Direct3D_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_YUREI);
	}
}

D3DXVECTOR3 Get_Dummy_Front(void)
{
	return D_Front;
}

D3DXVECTOR3 Get_Dummy_Right(void)
{
	return D_Right;
}

D3DXVECTOR3 Get_Dummy_Up(void)
{
	return D_Up;
}
D3DXVECTOR3 Get_Dummy_Pos(void)
{
	return Dummy;
}

float Get_Dummy_Ang(void)
{
	return DummyAng;
}

const SphereCollision* Dummy_GetCollision(void)
{
	return &Gost.Collision;
}