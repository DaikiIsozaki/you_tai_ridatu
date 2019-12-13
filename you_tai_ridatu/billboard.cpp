#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"

//頂点構造体
typedef struct BBVertex2D_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3	normal;//法線
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}BBVertex2D;

#define FVF_BBVERTEX3D (D3DFVF_XYZ| D3DFVF_NORMAL| D3DFVF_DIFFUSE| D3DFVF_TEX1)

static LPDIRECT3DVERTEXBUFFER9 g_pBbVertexBuffer = NULL;

static const BBVertex2D v[]//頂点データ
{
	{ D3DXVECTOR3(-0.5f,0.5f ,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
	{ D3DXVECTOR3(0.5f ,0.5f ,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f, 0.0f) },
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(0.5f ,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },
};

void BB_Init(void)
{
	//頂点バッファの確保
	Direct3D_GetDevice()->CreateVertexBuffer(sizeof(BBVertex2D)*4, D3DUSAGE_WRITEONLY, FVF_BBVERTEX3D, D3DPOOL_MANAGED, &g_pBbVertexBuffer, NULL);
}

void BB_Uninit(void)
{
	if (g_pBbVertexBuffer != NULL)
	{
		g_pBbVertexBuffer->Release();
	}
}

void BB_Draw(void)
{
	//Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする


	BBVertex2D* pV;
	//頂点バッファのロック
	g_pBbVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	g_pBbVertexBuffer->Unlock();
	//転送終了

	//ワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorldA;
	D3DXMatrixIdentity(&mtxWorldA);//単位行列を作る

	D3DXMATRIX mtxInvV;
	D3DXMatrixInverse(&mtxInvV,NULL,&Get_View());

	mtxInvV._41 = 0.0f;
	mtxInvV._42 = 0.0f;
	mtxInvV._43 = 0.0f;

	D3DXMATRIX mtxTranslation;
	D3DXMatrixTranslation(&mtxTranslation, 0, 3, 0);

	//行列の合成
	mtxWorldA = mtxInvV*mtxWorldA*mtxTranslation;
	Direct3D_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	//αテスト導入
	Direct3D_GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αテスト有効　デフォはFALSE
	Direct3D_GetDevice()->SetRenderState(D3DRS_ALPHAREF, 255);//第2引数は0～255の値を入れる　define,変数でも可
	Direct3D_GetDevice()->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);//GREATER＝"＞"

	/*
	//Zテスト
	Direct3D_GetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);//Zバッファへの書き込み
	Direct3D_GetDevice()->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	Direct3D_GetDevice()->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0, 1.0f, 0);//Zバッファのクリア	第1，2引数…矩形
	*/
	Direct3D_GetDevice()->SetFVF(FVF_BBVERTEX3D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(24));
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldA);//ワールド変換行列
	
	

	//Direct3D_GetDevice()->SetStreamSource(0, g_pBbVertexBuffer, 0, sizeof(BBVertex2D));
	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(BBVertex2D));

	D3DXMATRIX mtxTranslationA;
	D3DXMatrixTranslation(&mtxTranslationA, 0, 0.0f, 0);

	D3DXMATRIX mtxScaringA;
	D3DXMatrixScaling(&mtxScaringA, 2.0f, 2.0f, 2.0f);

	//行列の合成
	mtxWorldA = mtxInvV*mtxWorldA*mtxTranslationA*mtxScaringA;
	
	/*
	Direct3D_GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	Direct3D_GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	Direct3D_GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldA);//ワールド変換行列
	*/


	/*2
	BBVertex2D* pV2;
	//頂点バッファのロック
	g_pBbVertexBuffer->Lock(0, 0, (void**)&pV2, 0);
	memcpy(pV2, v, sizeof(v));
	g_pBbVertexBuffer->Unlock();
	//転送終了

	//ワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorldB;
	D3DXMatrixIdentity(&mtxWorldB);//単位行列を作る

	D3DXMATRIX mtxInvVB;
	D3DXMatrixInverse(&mtxInvVB, NULL, &Get_View());

	mtxInvVB._41 = 0.0f;
	mtxInvVB._42 = 0.0f;
	mtxInvVB._43 = 0.0f;

	D3DXMATRIX mtxTranslationB;
	D3DXMatrixTranslation(&mtxTranslationB, 3, 3, 0);

	//行列の合成
	mtxWorldB = mtxInvVB*mtxWorldB*mtxTranslationB;

	Direct3D_GetDevice()->SetFVF(FVF_BBVERTEX3D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(10));
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldB);//ワールド変換行列

	//Direct3D_GetDevice()->SetStreamSource(0, g_pBbVertexBuffer, 0, sizeof(BBVertex2D));
	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(BBVertex2D));

	*/


}

void BB_Exp_Draw(float x, float y, float z, float Bill_U ,int index)
{
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3D_GetDevice();

	BBVertex2D b_pori[] = {
		//正面
		{ D3DXVECTOR3(-4.0f,  4.0f, -4.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(Bill_U, 0.0f) },
		{ D3DXVECTOR3(4.0f,  4.0f, -4.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2((1.0f / 8) + Bill_U, 0.0f) },
		{ D3DXVECTOR3(-4.0f, -4.0f, -4.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(Bill_U, 1.0f) },
		{ D3DXVECTOR3(4.0f, -4.0f, -4.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2((1.0f / 8) + Bill_U, 1.0f) },
	};

	pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 70);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	D3DXMATRIX* mtxView = &Get_View();

	D3DXMATRIX mtxInvV;
	mtxView->_41 = 0.0f;
	mtxView->_42 = 0.0f;
	mtxView->_43 = 0.0f;
	D3DXMatrixInverse(&mtxInvV, NULL, mtxView);
	/*	mtxView->_14 = 0.0f;
	mtxView->_24 = 0.0f;
	mtxView->_34 = 0.0f;
	D3DXMatrixTranspose(&mtxInvV, mtxView);*/


	pD3DDevice->SetFVF(FVF_BBVERTEX3D);
	pD3DDevice->SetTexture(0, Texture_GetTexture(index));


	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;

	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixIdentity(&mtxTranslation);


	D3DXMatrixTranslation(&mtxTranslation, x, y, z);//平行


	mtxWorld = (mtxInvV * mtxWorld) * mtxTranslation;
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, b_pori, sizeof(BBVertex2D));

}

void BB_Exp_Draw2(float x, float y, float z,int index)
{
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3D_GetDevice();

	BBVertex2D b_pori[] = {
		//正面
		{ D3DXVECTOR3(-1.0f,  1.0f, -1.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 0.0f) },
		{ D3DXVECTOR3(1.0f,  1.0f, -1.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(1.0f, 0.0f) },
		{ D3DXVECTOR3(-1.0f, -1.0f, -1.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255), D3DXVECTOR2(0.0f, 1.0f) },
		{ D3DXVECTOR3(1.0f, -1.0f, -1.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),  D3DCOLOR_RGBA(255, 255, 255, 255),  D3DXVECTOR2(1.0f, 1.0f) },
	};

	pD3DDevice->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);
	pD3DDevice->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);

	pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 70);
	pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


	D3DXMATRIX* mtxView = &Get_View();

	D3DXMATRIX mtxInvV;
	mtxView->_41 = 0.0f;
	mtxView->_42 = 0.0f;
	mtxView->_43 = 0.0f;
	D3DXMatrixInverse(&mtxInvV, NULL, mtxView);
	mtxView->_14 = 0.0f;
	mtxView->_24 = 0.0f;
	mtxView->_34 = 0.0f;
	D3DXMatrixTranspose(&mtxInvV, mtxView);




	pD3DDevice->SetFVF(FVF_BBVERTEX3D);
	pD3DDevice->SetTexture(0, Texture_GetTexture(index));


	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;

	D3DXMatrixIdentity(&mtxWorld);
	D3DXMatrixIdentity(&mtxTranslation);


	D3DXMatrixTranslation(&mtxTranslation, x, y, z);//平行
	D3DXMatrixScaling(&mtxScaling, 0.5f, 0.5f, 0.5f);


	mtxWorld = (mtxInvV * mtxWorld)*mtxScaling * mtxTranslation;
	pD3DDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, b_pori, sizeof(BBVertex2D));

}