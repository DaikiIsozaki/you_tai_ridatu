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
#include"CoffeeCup.h"


static bool Syoumetu;
int TimeCount;
float angDodai = 0.0f;
float angCup = 0.0f;
D3DXMATRIX g_Save_Matrix;

void CC_Init(void)
{
	Syoumetu = false;
	TimeCount = 0;
	Model_Xfile_Load(INDEX_MODEL_COFFEE_CUP_BLUE);
	Model_Xfile_Load(INDEX_MODEL_COFFEE_CUP_KIIRO);
	Model_Xfile_Load(INDEX_MODEL_COFFEE_CUP_MIDORI);
	Model_Xfile_Load(INDEX_MODEL_DISH);
	Model_Xfile_Load(INDEX_MODEL_HERI_HONTAI);

}

void CC_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_COFFEE_CUP_BLUE);
	Model_Finalise(INDEX_MODEL_COFFEE_CUP_KIIRO);
	Model_Finalise(INDEX_MODEL_COFFEE_CUP_MIDORI);
	Model_Finalise(INDEX_MODEL_DISH);
	Model_Finalise(INDEX_MODEL_HERI_HONTAI);
}

void CC_Updete(void)
{
	angDodai+=0.2f;
	angCup -= 0.9f;
	

}

void Dodai_Draw(float x,float y,float z)
{
		Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
		Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, x, 1.0f+y, z);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(angDodai));
		D3DXMATRIX mtxScalingModel;
		D3DXMatrixScaling(&mtxScalingModel,2.0f,2.0f,2.0f);
		mtxWorldModel = mtxRotationModel*mtxScalingModel* mtxTranslationModel;
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_DISH);
		g_Save_Matrix = mtxWorldModel;

		CC_Blue_Draw();
		CC_Kiiro_Draw();
		CC_Midori_Draw();
		
		
}
/*
void CC_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る


	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f, -0.1f, 0.0f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(angCup));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_Matrix);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列

	Model_Draw(INDEX_MODEL_COFFEE_CUP);
}*/

void CC_Blue_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る


	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.7f, 0.0f, 0.2f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(angCup));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_Matrix);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	
	Model_Draw(INDEX_MODEL_COFFEE_CUP_BLUE);

}

void CC_Kiiro_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る


	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, -0.7f, 0.0f, 0.2f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(angCup));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;

	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_Matrix);


	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_COFFEE_CUP_KIIRO);
}

void CC_Midori_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る


	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f, 0.0f, -0.65f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(angCup));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;

	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_Matrix);


	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_COFFEE_CUP_MIDORI);
}

