#include "shadow.h"
#include "direct3d.h"
#include "texture.h"
#include "model.h"
#define SHADOW_MAX (4)
#define FVF_VERTEX3D (D3DFVF_XYZ |D3DFVF_DIFFUSE|D3DFVF_TEX1)

typedef struct Vertex3D_tag
{
	D3DXVECTOR3 potision;//D3DXVECTOR3←X,Y,Z
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}Vertex3D;

static const Vertex3D v[] = {
	//前                             //↓法線ベクトル(長さは必ず1にする)
	{ D3DXVECTOR3(-0.5f,0.0f,0.5f) ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(0.0f,0.0f) },//最後の二つUV座標
	{ D3DXVECTOR3(0.5f,0.0f,0.5f)  ,D3DCOLOR_RGBA(255,255,255,255), D3DXVECTOR2(1.0f,0.0f) },
	{ D3DXVECTOR3(-0.5f,0.0f,-0.5f),D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
	{ D3DXVECTOR3(0.5f,0.0f,-0.5f) ,D3DCOLOR_RGBA(255,255,255,255),  D3DXVECTOR2(1.0f,1.0f) },

}; typedef struct Shadow_tag
{
	float *cx, *cz;//座標 リンクさせる必要があるのでポインタにする
	float sx, sz;//拡大率
	bool create;//フラグ
}Shadow;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer2 = NULL;
static Shadow shadow[SHADOW_MAX] = { 0 };//影の最大数分作成
static Vertex3D *g_pVertex;
//↓こんな感じで呼び出す ポインターで座標を渡さないと付いてこないので注意！
//Shadow_Create(&tokage[index].world._41, &tokage[index].world._43, 3.4f, 3.4f, &tokage[index].shadow_number);
//消すとき
//Shadow_Destroy(tokage[index].shadow_number);←番号を渡す
void Shadow_Initialize(void)
{
	//とにかくグローバル変数をここで初期化
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		shadow[i].cx = NULL;
		shadow[i].cz = NULL;
		shadow[i].sx = 0.0f;
		shadow[i].sz = 0.0f;
		shadow[i].create = false;
	}

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	if (!pDevice) return;

	// 頂点バッファの確保（頂点４つ分）
	pDevice->CreateVertexBuffer(sizeof(v), D3DUSAGE_WRITEONLY, FVF_VERTEX3D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	// インデックスバッファの確保（インデックス６個分）
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer2, NULL);

	// 頂点インデックスバッファへ頂点インデックスの書き込み

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pVertex, 0);
	memcpy(g_pVertex, v, sizeof(v));
	g_pVertexBuffer->Unlock();

	WORD index[] = {//1つ目
		0,1,2,
		1,3,2,
	};
	WORD* pIndex;
	g_pIndexBuffer2->Lock(0, 0, (void**)&pIndex, 0);
	memcpy(pIndex, index, sizeof(index));
	g_pIndexBuffer2->Unlock();
}

void Shadow_Create(float* x, float* y, float scaleX, float scaleY, int* shadow_number)
{
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (!shadow[i].create)
		{
			shadow[i].cx = x;
			shadow[i].cz = y;
			shadow[i].sx = scaleX;
			shadow[i].sz = scaleY;
			shadow[i].create = true;
			*shadow_number = i;
			break;
		}
	}
}

void Shadow_Finalize(void)
{

}

void Shadow_Update(void)
{

}

void Shadow_Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();//ゲッター
	/*4×4行列*/D3DXMATRIX mtx;
	/*4×4行列*/D3DXMATRIX mtx2;
	/*4×4行列*/D3DXMATRIX mtx3;
	/*4×4行列*/D3DXMATRIX mtx4;
	//D3DXMatrixTranslation(&mtx, 1, 1, 1);//平行移動 x y z
	//D3DXMatrixRotationYawPitchRoll(&mtx2, D3DXToRadian(radian), D3DXToRadian(radian), D3DXToRadian(radian));
	//D3DXMatrixRotationX(&mtx2, D3DXToRadian(radian));
	/*4×4行列*/D3DXMATRIX mtxworld;
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);//ライトOFF
	for (int i = 0; i < SHADOW_MAX; i++)
	{
		if (shadow[i].create)
		{
			//減算合成(設定して●影を書いたら戻す(アルファブレンドを行う))
			//D3DXMatrixRotationY(mtx2, D3DXToRadian(radian));
			D3DXMatrixIdentity(&mtxworld);//単位行列を作る。単位行列を作る関数には大抵Identityが付いてる
			D3DXMatrixTranslation(&mtx, *shadow[i].cx, 0.1f, *shadow[i].cz);//平行移動 x y z
			D3DXMatrixScaling(&mtx2, shadow[i].sx, 0.1f, shadow[i].sz);//拡大　x y zの拡大
			D3DXMatrixRotationY(&mtx3, D3DXToRadian(0));

			mtxworld = mtx3 * mtx2 * mtx;//原点が中心！
			pDevice->SetTransform(D3DTS_WORLD, &mtxworld);//セットした行列をワールド座標にする

			pDevice->SetTexture(0, Texture_GetTexture(31));

			pDevice->SetFVF(FVF_VERTEX3D);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//引き算する量をSRCALPHAで調節

			pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex3D)); // 頂点バッファの設定
			pDevice->SetIndices(g_pIndexBuffer2);

			pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 12);

			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);			
		}
	}
}

void Shadow_Destroy(int number)
{
	shadow[number].cx = NULL;
	shadow[number].cz = NULL;
	shadow[number].sx = 0.0f;
	shadow[number].sz = 0.0f;
	shadow[number].create = false;
}