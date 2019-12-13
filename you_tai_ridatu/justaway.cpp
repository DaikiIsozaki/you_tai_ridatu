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
#include"justaway.h"
#include"input.h"

D3DXMATRIX g_Save_MatrixJustaway;
float JustawayJump;
float JustawayRotation;
float JustawayRotationA;

bool BJustawayJump;



void Justaway_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_JUSTAWAY_BODY);
	Model_Xfile_Load(INDEX_MODEL_JUSTAWAY_HEAD);
	Model_Xfile_Load(INDEX_MODEL_JUSTAWAY_LEFTARM);
	Model_Xfile_Load(INDEX_MODEL_JUSTAWAY_RIGHTARM);
	Model_Xfile_Load(INDEX_MODEL_TRAMPORINE_MAIN);
	
	JustawayJump = 0.0f;
	JustawayRotation = 0.0f;
	JustawayRotationA = 0.0f;
	BJustawayJump = false;

}

void Justaway_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_JUSTAWAY_BODY);
	Model_Finalise(INDEX_MODEL_JUSTAWAY_HEAD);
	Model_Finalise(INDEX_MODEL_JUSTAWAY_LEFTARM);
	Model_Finalise(INDEX_MODEL_JUSTAWAY_RIGHTARM);
	Model_Finalise(INDEX_MODEL_TRAMPORINE_MAIN);
}

void Justaway_Update(void)
{
	if(Keyboard_IsPress(DIK_RETURN))
	{
		JustawayRotationA += 0.001f;
	}
	if (Keyboard_IsPress(DIK_BACK))
	{
		JustawayRotationA = 0.0f;
	}
	JustawayRotation += JustawayRotationA;

	
	if (!BJustawayJump)
	{
		JustawayJump += 0.05f;
		if (JustawayJump >= 10.0f)
		{
			BJustawayJump = true;
		}
	}

	if (BJustawayJump)
	{
		JustawayJump -= 0.02f;
		if (JustawayJump < 0.4f)
		{
			BJustawayJump = false;
		}
	}
	


}

void Justaway_body_Draw(float x, float y, float z)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, x, 1.0f + y+JustawayJump, z);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(90));
	D3DXMATRIX mtxScalingModel;
	D3DXMatrixScaling(&mtxScalingModel, 2.0f, 2.0f, 2.0f);

	mtxWorldModel = mtxScalingModel*mtxRotationModel* mtxTranslationModel;
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_JUSTAWAY_BODY);

	g_Save_MatrixJustaway = mtxWorldModel;

	Justaway_head_Draw();
	Justaway_LArm_Draw();
	Justaway_RArm_Draw();
	Trampoline_main_Draw();
}
void Justaway_head_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f,0.0f, 0.0f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(JustawayRotation));

	mtxWorldModel = mtxTranslationModel*mtxRotationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixJustaway);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列

	Model_Draw(INDEX_MODEL_JUSTAWAY_HEAD);
}

void Justaway_LArm_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f, 0.0f, 0.0f);
	
	mtxWorldModel =mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixJustaway);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列

	Model_Draw(INDEX_MODEL_JUSTAWAY_LEFTARM);
}

void Justaway_RArm_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f, 0.0f, 0.0f);

	mtxWorldModel = mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixJustaway);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列

	Model_Draw(INDEX_MODEL_JUSTAWAY_RIGHTARM);
}
void Trampoline_main_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 0.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxScalingModel;
	D3DXMatrixScaling(&mtxScalingModel, 2.0f, 2.0f, 2.0f);

	mtxWorldModel = mtxScalingModel* mtxTranslationModel;
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
}

void Tramporine_sub_Draw(void)
{

}

