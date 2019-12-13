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
typedef struct CubeVertex3D_tag
{
	D3DXVECTOR3 position;
	D3DXVECTOR3	normal;//法線
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}CubeVertex3D;

#define FVF_CUBEVERTEX3D	(D3DFVF_XYZ| D3DFVF_NORMAL| D3DFVF_DIFFUSE| D3DFVF_TEX1)//FVFの定義

//グローバル変数
static float a = 0.0f;
static float b = 0.0f;
static float c = 1.0f;
static float d, e, f, g, h;
static bool i, j, k, l, m;
static float x, y, z;
static bool Kf;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static const CubeVertex3D v[]//頂点データ
{
	//正面								//長さは1にする
	{ D3DXVECTOR3(-0.5f,0.5f ,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.00f,0.0f) },
	{ D3DXVECTOR3(0.5f ,0.5f ,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.00) },
	{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f) },
									
	//{ D3DXVECTOR3(-0.5f,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.25f) },
	//{ D3DXVECTOR3(0.5f ,0.5f ,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.0f) },
	{ D3DXVECTOR3(0.5f ,-0.5f,-0.5f),D3DXVECTOR3(0.0f,0.0f,-1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25f,0.25f) },

	//右
	{ D3DXVECTOR3(0.5f,  0.5f,  -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.0) },
	{ D3DXVECTOR3(0.5f,  0.5f,   0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.0) },
	{ D3DXVECTOR3(0.5f, -0.5f,  -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.25) },
												  
	//{ D3DXVECTOR3(0.5f, -0.5f,  -0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.25) },
	//{ D3DXVECTOR3(0.5f,  0.5f,   0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.0) },
	{ D3DXVECTOR3(0.5f, -0.5f,   0.5f),D3DXVECTOR3(1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.25) },

	//上
	{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.0) },
	{ D3DXVECTOR3(0.5f,  0.5f, 0.5f) ,D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.0) },
	{ D3DXVECTOR3(-0.5f,  0.5f,-0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.25) },
												 
	//{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.25) },
	//{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.0) },
	{ D3DXVECTOR3(0.5f,  0.5f, -0.5f),D3DXVECTOR3(0.0f,1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.25) },

	//左
	{ D3DXVECTOR3(-0.5f,  0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.0) },
	{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.25) },
												   
	//{ D3DXVECTOR3(-0.5f, -0.5f,  0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.75, 0.25) },
	//{ D3DXVECTOR3(-0.5f,  0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0, 0.0) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),D3DXVECTOR3(-1.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0, 0.25) },
	//後ろ
	{ D3DXVECTOR3(0.5f,  0.5f,  0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0, 0.25) },
	{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.25) },
	{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0, 0.50) },
												  
	//{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0, 0.50) },
	//{ D3DXVECTOR3(-0.5f,  0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.25) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,0.0f,1.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.50) },

	//下
	{ D3DXVECTOR3(-0.5f, -0.5f,-0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.25) },//31
	{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.25) },//32
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.50) },//33
												 
	//{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.25, 0.50) },//34
	//{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.25) },//35
	{ D3DXVECTOR3(0.5f, -0.5f,  0.5f),D3DXVECTOR3(0.0f,-1.0f,0.0f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.50, 0.50) },//36

};



void Cube_Init(void) 
{
	d, e, f, g, h = 0.0f;
	i = true;
	j = true;
	k = true;
	l = true;
	m = true;
	x = 1.0f;
	y = 1.0f;
	z = 1.0f;
	Kf = true;

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	//頂点バッファの確保
	Direct3D_GetDevice()->CreateVertexBuffer(sizeof(CubeVertex3D) * 24, D3DUSAGE_WRITEONLY, FVF_CUBEVERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	//インデックスバッファの確保
	Direct3D_GetDevice()->CreateIndexBuffer(sizeof(WORD) * 36, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
}

void Cube_Uninit(void)
{
	//頂点バッファの解放
	if (g_pVertexBuffer != NULL)
	{
		g_pVertexBuffer->Release();
	}
	if (g_pIndexBuffer != NULL)
	{
		g_pIndexBuffer->Release();
	}
}

void Cube_Update(void)
{
	a += 0.5f;

	if (i)
	{
		d += 0.010f;
		if (d >= 4.0f)
		{
			d = 4.0f;
			i = false;
		}
	}

	if (j&&!i)
	{
		e += 0.009f;
		if (e >= 4.0f)
		{
			e = 4.0f;
			j = false;
		}
	}

	if (k && !j)
	{
		f += 0.008f;
		if (f >= 4.0f)
		{
			f = 4.0f;
			k = false;
		}
	}
	if (l && !k)
	{
		g += 0.007f;
		if (g >= 4.0f)
		{
			g = 4.0f;
			l = false;
		}
	}
	if (m && !l)
	{
		h += 0.007f;
		if (h >= 4.0f)
		{
			h = 4.0f;
			m = false;
		}
	}
	if (i == false&&j == false&& k == false&& l == false&& m == false)
	{
		i = true;
		j = true;
		k = true;
		l = true;
		m = true;
		d = 0.0f;
		e = 0.0f;
		f = 0.0f;
		g = 0.0f;
		h = 0.0f;
	}
}

void Cube_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする
	//Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする

	//仮想アドレス
	CubeVertex3D* pV;
	//頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();
	//転送終了


	//頂点インデックス
	WORD index[] = {
		0,1,2,2,1,3,
		4,5,6,6,5,7,
		8,9,10,10,9,11,
		12,13,14,14,13,15,
		16,17,18,18,17,19,
		20,21,22,22,21,23,
	};
	//VRAMへの転送
	//インデックスバッファのLock
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	g_pIndexBuffer->Unlock();

	//ワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorld;
	// (4*4)

	D3DXMatrixIdentity(&mtxWorld);//単位行列を作る

	//平行
	D3DXMATRIX mtxTranslation;
	D3DXMatrixTranslation(&mtxTranslation, -4.5f + CubeX(), 0.5f, 4.5f + CubeZ());
	//回転
	D3DXMATRIX mtxRotation;
	D3DXMatrixRotationY(&mtxRotation, D3DXToRadian(a));

	//行列の合成
	mtxWorld = mtxRotation*mtxTranslation;
	//mtxWorld = mtxRotation;

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(23));
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,24,0,12);


	//2個目
	D3DXMATRIX mtxTranslation2;
	D3DXMatrixTranslation(&mtxTranslation2, -0.5f, 0.5f, 0.5f);
	D3DXMATRIX mtxTranslation10;
	D3DXMatrixTranslation(&mtxTranslation10, 5.0f, 0.0f, -5.0f);
	D3DXMATRIX mtxScaling2;
	D3DXMatrixIdentity(&mtxWorld);
	for (int i = 0;i < 10;i++)
	{
		if (Kf)
		{
			x += 0.0001f;
			y += 0.0001f;
			z += 0.0001f;
		}
		D3DXMatrixScaling(&mtxScaling2, x, y, z);

		if (x > 2.0f)
		{
			Kf = false;
		}
		if (x < 0.0f)
		{
			Kf = true;
		}
		if (!Kf)
		{
			x -= 0.0001f;
			y -= 0.0001f;
			z -= 0.0001f;
		}
	}
	mtxWorld = mtxTranslation2*mtxScaling2*mtxTranslation10;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);


	//3個目
	D3DXMATRIX mtxTranslation3;
	D3DXMatrixTranslation(&mtxTranslation3, -4.5f, 4.5f - d, -4.5f);

	mtxWorld = mtxTranslation3;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列
	

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);
	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//4個目
	D3DXMATRIX mtxTranslation4;
	D3DXMatrixTranslation(&mtxTranslation4, -4.5f, 5.5f - e, -4.5f);

	mtxWorld = mtxTranslation4;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列
	

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//5個目
	D3DXMATRIX mtxTranslation5;
	D3DXMatrixTranslation(&mtxTranslation5, -4.5f, 6.5f - f, -4.5f);

	mtxWorld = mtxTranslation5;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列
	

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//6個目
	D3DXMATRIX mtxTranslation6;
	D3DXMatrixTranslation(&mtxTranslation6, -4.5f, 7.5f - g, -4.5f);

	mtxWorld = mtxTranslation6;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列


	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//7個目
	D3DXMATRIX mtxTranslation7;
	D3DXMatrixTranslation(&mtxTranslation7, -4.5f, 8.5f - h, -4.5f);

	mtxWorld = mtxTranslation7;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列
	

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//8個目
	D3DXMATRIX mtxTranslation8;
	D3DXMatrixTranslation(&mtxTranslation8, -4.5f, 0.5f, 4.5f);

	mtxWorld = mtxTranslation8;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);

	//9個目
	D3DXMATRIX mtxTranslation9;
	D3DXMatrixTranslation(&mtxTranslation9, Get_Cube().x, Get_Cube().y, Get_Cube().z);


	mtxWorld = mtxTranslation9;

	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列

	Direct3D_GetDevice()->SetFVF(FVF_CUBEVERTEX3D);

	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(CubeVertex3D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);
	//Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);


}