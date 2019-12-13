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

void Komono_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_ISU);
	Model_Xfile_Load(INDEX_MODEL_GAITOU);
	Model_Xfile_Load(INDEX_MODEL_KING);
}

void Komono_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_ISU);
	Model_Finalise(INDEX_MODEL_GAITOU);
	Model_Finalise(INDEX_MODEL_KING);
}

void Komono_Update(void)
{

}

void Komono_Gaitou_Draw(int index, float x, float y, float z)
{
		Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);

		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, x, 1.0f + y, z);
		D3DXMATRIX mtxScalingModel;
		D3DXMatrixScaling(&mtxScalingModel, 2.0f, 2.0f, 2.0f);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(180));
		mtxWorldModel =mtxRotationModel* mtxScalingModel* mtxTranslationModel;
		Direct3D_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(index);

	
}