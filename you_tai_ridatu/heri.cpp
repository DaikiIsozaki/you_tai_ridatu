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

D3DXVECTOR3 H_at(0.0f, 10.0f, -10.0f);

D3DXMATRIX g_Save_Matrix2;
float puroperaAng=0.0f;
bool bullet_flag;
float HeriAng=0.0f;
float HeriTakasa = 0.0f;
D3DXVECTOR3 CHeri;
float SpeedHeri;
D3DXVECTOR3 HFront;//カメラの向きベクトル(単位ベクトル)※必ず長さ1
D3DXVECTOR3 HRight;
D3DXVECTOR3 HUp;
static float Length;

void Heri_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_HERI_HONTAI);
	Model_Xfile_Load(INDEX_MODEL_HERI_PUROPERA);
	bullet_flag=false;
	CHeri = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	HFront = D3DXVECTOR3(0.0f, -0.5f, 1.0f);
	HUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&HRight, &HFront, &HUp);
	D3DXVec3Normalize(&HRight, &HRight);
	D3DXVec3Cross(&HUp, &HRight, &HFront);
	D3DXVec3Normalize(&HUp, &HUp);

	D3DXVec3Normalize(&HFront, &HFront);
	SpeedHeri = 0.02f;
	Length = 10.0f;
}

void Heri_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_HERI_HONTAI);
	Model_Finalise(INDEX_MODEL_HERI_PUROPERA);
}

void Heri_Updete(void)
{
	/*
	//ヘリ移動
	if (Keyboard_IsPress(DIK_1))
	{
		D3DXVECTOR3 f(HFront);
		f.y = 0.0f;
		CHeri += f*SpeedHeri;

	}
	if (Keyboard_IsPress(DIK_2))
	{
		D3DXVECTOR3 f(HFront);
		f.y = 0.0f;
		CHeri -= f*SpeedHeri;
	}
	if (Keyboard_IsPress(DIK_4))
	{
		D3DXVECTOR3 f(HRight);

		CHeri -= f*SpeedHeri;
	}
	if (Keyboard_IsPress(DIK_3))
	{
		D3DXVECTOR3 f(HRight);

		CHeri += f*SpeedHeri;
	}

	puroperaAng += 2.0f;
	if (Keyboard_IsTrigger(DIK_5))
	{
		HeriAng -= 45.0f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(-45));
		D3DXVec3TransformNormal(&HFront, &HFront, &mtxR);
		D3DXVec3TransformNormal(&HRight, &HRight, &mtxR);
		D3DXVec3TransformNormal(&HUp, &HUp, &mtxR);
		
	}
	if (Keyboard_IsTrigger(DIK_6))
	{
		HeriAng += 45.0f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(45));
		D3DXVec3TransformNormal(&HFront, &HFront, &mtxR);
		D3DXVec3TransformNormal(&HRight, &HRight, &mtxR);
		D3DXVec3TransformNormal(&HUp, &HUp, &mtxR);
		
	}
	if (Keyboard_IsPress(DIK_7))
	{
		HeriTakasa -= 0.05f;
	}
	if (Keyboard_IsPress(DIK_8))
	{
		HeriTakasa += 0.05f;
	}
	if (Keyboard_IsPress(DIK_0))
	{
		HeriAng += 10.0f;
		puroperaAng = 0;
	}
	if (Keyboard_IsPress(DIK_SPACE))
	{
		Bullet_Draw(CHeri.x,CHeri.y,CHeri.z);
	}
	*/
}
void Heri_Draw(float x, float y, float z)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, x+CHeri.x, y+HeriTakasa, z+ CHeri.z);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(HeriAng));
	D3DXMATRIX mtxScalingModel;
	D3DXMatrixScaling(&mtxScalingModel, 1.0f, 1.0f, 1.0f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(90));
	mtxWorldModel = mtxRotationModel2* mtxRotationModel*mtxScalingModel* mtxTranslationModel;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_HERI_HONTAI);
	g_Save_Matrix2 = mtxWorldModel;

	Heri_Puropera_Draw();	
}

void Heri_Puropera_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.45f, 2.3f, 0.0f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(puroperaAng));

	mtxWorldModel2 = mtxRotationModel*mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_Matrix2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_HERI_PUROPERA);

	//横プロペラ
	D3DXMATRIX mtxTranslationModel3;
	D3DXMatrixTranslation(&mtxTranslationModel2, 4.5f, 2.7f, -0.7f);
	D3DXMATRIX mtxRotationModel3;
	D3DXMatrixRotationZ(&mtxRotationModel3, D3DXToRadian(puroperaAng));
	D3DXMATRIX mtxRotationModel3a;
	D3DXMatrixRotationX(&mtxRotationModel3a, D3DXToRadian(90));
	D3DXMATRIX mtxScaringModel3;
	D3DXMatrixScaling(&mtxScaringModel3, 0.5f, 0.5f, 0.5f);


	mtxWorldModel2 =mtxRotationModel3a*mtxRotationModel3*mtxScaringModel3*mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_Matrix2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_HERI_PUROPERA);


}

D3DXVECTOR3 Get_HeriFront(void)
{
	return HFront;
}
