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
#include"soukousya.h"
#include"bullet.h"

#define SOUKOUSYA_SPEED	(0.01f)

typedef struct TankParts_tag
{
	int ChildIndex;//Parts* pChild;
	int sibling;//兄弟いない時は-1
	D3DXVECTOR3 OffsetR;
	D3DXVECTOR3 OffsetT;
	D3DXVECTOR3 Rotation;
	int Madel;

}TankParts;

static TankParts g_TankData[]=
{
	{1,-1,D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),0},
	{8,2,D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,1.5f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),0 },

};

D3DXMATRIX g_Save_MatrixSoukousya;
D3DXMATRIX g_Save_MatrixSoukousya2;
D3DXMATRIX g_Save_MatrixSoukousya3;
D3DXMATRIX g_Save_MatrixSoukousya4;

D3DXVECTOR3 CSoukousya;
D3DXVECTOR3 SFront;
D3DXVECTOR3 SRight;
D3DXVECTOR3 SUp;

D3DXVECTOR3 CSoukousya_Dodai;
D3DXVECTOR3 S_DFront;
D3DXVECTOR3 S_DRight;
D3DXVECTOR3 S_DUp;
float Soukousya_muki=0.0f;

int TaiyaAng = 0;
int TaiyaAng2 = 0;

float DodaiAng = 0.0f;
float HoudaiAng = 0.0f;

int  cnt2 = 0;


void Soukousya_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_BODY);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_SYASHI);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_KIJU_DODAI);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_KIJU);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_TAIYA);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_TAIYA2);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_TAIYA3);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA_TAIYA4);

	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_BODY);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_HOUDAI);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_HOUDAI_DODAI);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_KIJU);
	Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_TAIYA);
	Model_Xfile_Load(INDEX_MODEL_MARU);

	CSoukousya = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	SUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&SRight, &SFront, &SUp);
	D3DXVec3Normalize(&SRight, &SRight);
	D3DXVec3Cross(&SUp, &SRight, &SFront);
	D3DXVec3Normalize(&SUp, &SUp);
	D3DXVec3Normalize(&SFront, &SFront);


	CSoukousya_Dodai = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	S_DFront = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	S_DUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&S_DRight, &S_DFront, &S_DUp);
	D3DXVec3Normalize(&S_DRight, &S_DRight);
	D3DXVec3Cross(&S_DUp, &S_DRight, &S_DFront);
	D3DXVec3Normalize(&S_DUp, &S_DUp);
	D3DXVec3Normalize(&S_DFront, &S_DFront);
	

	//初期化
	//g_TankData[0].Madel = Model_Xfile_Load(INDEX_MODEL_SOUKOUSYA1_BODY);


}

void Soukousya_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_BODY);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_SYASHI);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_KIJU_DODAI);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_KIJU);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_TAIYA);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_TAIYA2);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_TAIYA3);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA_TAIYA4);

	Model_Finalise(INDEX_MODEL_SOUKOUSYA1_BODY);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA1_HOUDAI);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA1_HOUDAI_DODAI);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA1_KIJU);
	Model_Finalise(INDEX_MODEL_SOUKOUSYA1_TAIYA);
	Model_Finalise(INDEX_MODEL_MARU);

}

void Soukousya_Updete(void)
{
	//移動
	if (Keyboard_IsPress(DIK_1))
	{
		D3DXVECTOR3 f(SFront);
		f.y = 0.0f;
		CSoukousya += f*SOUKOUSYA_SPEED;

		TaiyaAng += 1;

	}
	if (Keyboard_IsPress(DIK_2))
	{
		D3DXVECTOR3 f(SFront);
		f.y = 0.0f;
		CSoukousya -= f*SOUKOUSYA_SPEED;

		TaiyaAng -= 1;
	}
	
	if (Keyboard_IsPress(DIK_3))
	{
		Soukousya_muki -=0.1f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.1f));
		D3DXVec3TransformNormal(&SFront, &SFront, &mtxR);
		D3DXVec3TransformNormal(&SRight, &SRight, &mtxR);
		D3DXVec3TransformNormal(&SUp, &SUp, &mtxR);

	}
	if (Keyboard_IsPress(DIK_4))
	{
		Soukousya_muki += 0.1f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.1f));
		D3DXVec3TransformNormal(&SFront, &SFront, &mtxR);
		D3DXVec3TransformNormal(&SRight, &SRight, &mtxR);
		D3DXVec3TransformNormal(&SUp, &SUp, &mtxR);

	}

	if (Keyboard_IsPress(DIK_5))
	{
		DodaiAng -= 0.1f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.1f));
		D3DXVec3TransformNormal(&S_DFront, &S_DFront, &mtxR);
		D3DXVec3TransformNormal(&S_DRight, &S_DRight, &mtxR);
		D3DXVec3TransformNormal(&S_DUp, &S_DUp, &mtxR);
	}
	if (Keyboard_IsPress(DIK_6))
	{
		DodaiAng+= 0.1f;
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.1f));
		D3DXVec3TransformNormal(&S_DFront, &S_DFront, &mtxR);
		D3DXVec3TransformNormal(&S_DRight, &S_DRight, &mtxR);
		D3DXVec3TransformNormal(&S_DUp, &S_DUp, &mtxR);
	}
	
	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		Bullet_Create(CSoukousya.x, CSoukousya.y+3.0f, CSoukousya.z-1.0f);
	}
}
/*
void Soukousya_Draw(float x, float y, float z)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, x+CSoukousya.x , y , z+CSoukousya.z );

	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(Soukousya_muki));
	
	mtxWorldModel = mtxRotationModel*mtxTranslationModel;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA_BODY);
	g_Save_MatrixSoukousya = mtxWorldModel;

	Soukousya_Syashi_Draw();
	Soukousya_Taiya_Draw();
	Soukousya_Juza();
	Soukousya_Kiju();
}

void Soukousya_Syashi_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.0f, 0.0f, 0.0f);
	
	mtxWorldModel2 =mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA_SYASHI);
}

void Soukousya_Taiya_Draw(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.0f, 0.0f, 0.0f);
	

	mtxWorldModel2 = mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA_TAIYA);
	Model_Draw(INDEX_MODEL_SOUKOUSYA_TAIYA2);
	Model_Draw(INDEX_MODEL_SOUKOUSYA_TAIYA3);
	Model_Draw(INDEX_MODEL_SOUKOUSYA_TAIYA4);
	

}

void Soukousya_Juza(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.4f, 2.5f, -0.3f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(DodaiAng));

	mtxWorldModel2 =mtxRotationModel2*mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA_KIJU_DODAI);
	g_Save_MatrixSoukousya4 = mtxRotationModel2;
}

void Soukousya_Kiju(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.8f, 2.5f, -0.3f);

	mtxWorldModel2 = mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya4);
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya);
	
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA_KIJU);
}
*/

void Soukousya1_body(float x, float y, float z)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る

	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, x + CSoukousya.x, y, z + CSoukousya.z);

	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(Soukousya_muki));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_BODY);
	g_Save_MatrixSoukousya2 = mtxWorldModel;

	Soukousya1_houdai();
	Soukousya1_houdai_dodai();
	Soukousya1_kiju();
	Soukousya1_Left();
	Soukousya1_Right();

}

void Soukousya1_houdai_dodai(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, CSoukousya_Dodai.x, CSoukousya_Dodai.y ,CSoukousya_Dodai.z);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(DodaiAng));

	mtxWorldModel2 =mtxRotationModel2* mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_HOUDAI_DODAI);

	g_Save_MatrixSoukousya3 = mtxWorldModel2;
}

void Soukousya1_houdai(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.0f, 0.0f, 0.0f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(TaiyaAng));

	mtxWorldModel2 = mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya3);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_HOUDAI);
}



void Soukousya1_kiju(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 0.0f, 0.0f, 0.0f);

	mtxWorldModel2 = mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_KIJU);
}

void Soukousya1_Left(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, -1.5f, 0.8f, 1.8f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationX(&mtxRotationModel2,D3DXToRadian(TaiyaAng));


	mtxWorldModel2 = mtxRotationModel2*mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);

	//2
	D3DXMATRIX mtxWorldModel3;
	D3DXMatrixIdentity(&mtxWorldModel3);//単位行列を作る

	D3DXMATRIX mtxTranslationModel3;
	D3DXMatrixTranslation(&mtxTranslationModel3, -1.5f, 0.8f, -0.5f);
	D3DXMATRIX mtxRotationModel3;
	D3DXMatrixRotationX(&mtxRotationModel3, D3DXToRadian(TaiyaAng));

	mtxWorldModel3 = mtxRotationModel3*mtxTranslationModel3;
	D3DXMatrixMultiply(&mtxWorldModel3, &mtxWorldModel3, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel3);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);


	//3
	D3DXMATRIX mtxWorldModel4;
	D3DXMatrixIdentity(&mtxWorldModel4);//単位行列を作る

	D3DXMATRIX mtxTranslationModel4;
	D3DXMatrixTranslation(&mtxTranslationModel4, -1.5f, 0.8f, -2.9f);
	D3DXMATRIX mtxRotationModel4;
	D3DXMatrixRotationX(&mtxRotationModel4, D3DXToRadian(TaiyaAng));

	mtxWorldModel4 = mtxRotationModel4*mtxTranslationModel4;
	D3DXMatrixMultiply(&mtxWorldModel4, &mtxWorldModel4, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel4);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);
}

void Soukousya1_Right(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る

	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, 1.5f, 0.8f, 1.8f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(TaiyaAng));
	
	mtxWorldModel2 =mtxRotationModel2* mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);

	//2
	D3DXMATRIX mtxWorldModel3;
	D3DXMatrixIdentity(&mtxWorldModel3);//単位行列を作る

	D3DXMATRIX mtxTranslationModel3;
	D3DXMatrixTranslation(&mtxTranslationModel3, 1.5f, 0.8f, -0.5f);
	D3DXMATRIX mtxRotationModel3;
	D3DXMatrixRotationX(&mtxRotationModel3, D3DXToRadian(TaiyaAng));

	mtxWorldModel3 = mtxRotationModel3*mtxTranslationModel3;
	D3DXMatrixMultiply(&mtxWorldModel3, &mtxWorldModel3, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel3);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);


	//3
	D3DXMATRIX mtxWorldModel4;
	D3DXMatrixIdentity(&mtxWorldModel4);//単位行列を作る

	D3DXMATRIX mtxTranslationModel4;
	D3DXMatrixTranslation(&mtxTranslationModel4, 1.5f, 0.8f, -2.9f);
	D3DXMATRIX mtxRotationModel4;
	D3DXMatrixRotationX(&mtxRotationModel4, D3DXToRadian(TaiyaAng));

	mtxWorldModel4 = mtxRotationModel4*mtxTranslationModel4;
	D3DXMatrixMultiply(&mtxWorldModel4, &mtxWorldModel4, &g_Save_MatrixSoukousya2);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel4);//ワールド変換行列
	Model_Draw(INDEX_MODEL_SOUKOUSYA1_TAIYA);
}

/*void Parts_Draw(const Parts* p,const D3DXMATRIX* pMtx)
{
	D3DXMATRIX mtxOffsetR,mtxOffsetT,mtxRotation,mtxWorld;

	D3DXMatrixYawPitchRoll(&mtxOffsetR,p->offsetR.y,p->offsetR.x,p->offsetR.z);
	D3DXMatrixTranslation(&mtxOffsetT,p->offsetT.x,p->offsetT.y,p->offsetT.z);
	D3DXMatrixYawPitchRoll(&mtxRotation,p->rotation.y,p->rotation.x,p->rotation.z);

	mtxWorld=mtxRotation*mtxOffsetR*mtxOffsetT*(*pMtx);

	//Draw関数
	if(p->sibling>=0)
	{
		Parts_Draw(&g_tankData[p->sibling],pMtx);
	}
	if(p->Child>=0)
	{
		PartsDraw(&g_TankData[p->Child],&mtxWorld);
	}

}*/

D3DXVECTOR3 Get_tank(void)
{
	return SFront;
}

D3DXVECTOR3 Get_TankPos(void)
{
	return CSoukousya;
}
