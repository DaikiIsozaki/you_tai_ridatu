#include<Windows.h>

#define _USE_MATH_DEFINES
#include"math.h"
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"sprite.h"
#include"string.h"

#define FVF_VERTEX2D (D3DFVF_XYZRHW| D3DFVF_DIFFUSE| D3DFVF_TEX1)
//構造体宣言
typedef struct Vertex2D_tag
{
	D3DXVECTOR4 position;	//floatにして4つ目1.0f(RHW)	座標交換済み頂点
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;

}Vertex2D;
//グローバル変数宣言
static D3DCOLOR g_Color = 0xffffffff;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

float x_ = 500.0f;
float y_ = 300.0f;
float Long = 150.0f;		//長さ
float Angle = 36.0f;	//角度
float Angle2 = 0.0f;
float Angle3 = 1.0f;



void Sprite_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	//頂点バッファの確保
	Direct3D_GetDevice()->CreateVertexBuffer(sizeof(Vertex2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	//インデックスバッファの確保
	Direct3D_GetDevice()->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);


}
void Sprite_Finalize(void)
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

void SetColor(D3DCOLOR color)
{
	g_Color = color;
}

void Sprite_Draw(int texture_index, float dx, float dy, float rate)
{
	LPDIRECT3DDEVICE9 Direct3D_GetDevice();



	float w = Texture_GetWidth(texture_index)*rate;
	float h = Texture_GetHeight(texture_index)*rate;





	Vertex2D v[]
	{

		/*{ D3DXVECTOR4(100.0f	,100.0f			,1.0f,1.0f)	,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(100.0f	,100.0f			,1.0f,1.0f)	,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(100.0f	,100.0f			,1.0f,1.0f)	,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(100.0f	,100.0f			,1.0f,1.0f)	,D3DCOLOR_RGBA(255,255,255,255),D3DXVECTOR2(1.0f,1.0f) },*/


		{ D3DXVECTOR4(dx		,dy			,1.0f,1.0f)	,g_Color , D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(dx + w		,dy			,1.0f,1.0f)	,g_Color , D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(dx		,dy + h		,1.0f,1.0f)	,g_Color , D3DXVECTOR2(0.0f,1.0f) },


		//{ D3DXVECTOR4(dx+w		,dy+h		,1.0f,1.0f)	,g_Color },
		{ D3DXVECTOR4(dx + w		,dy + h		,1.0f,1.0f)	,g_Color, D3DXVECTOR2(1.0f,1.0f) },
		//{ D3DXVECTOR4(dx + w		,dy + h		,1.0f,1.0f)	,g_Color },




	};

	//頂点インデックス
	WORD index[] = {
		0,1,2,
		1,3,2
	};

	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(texture_index));
	//④
	Direct3D_GetDevice()->SetFVF(FVF_VERTEX2D);


	//⑤												/*プリミティブ数*/
	//Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, v, sizeof(Vertex2D));
	Direct3D_GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2, index, D3DFMT_INDEX16, v, sizeof(Vertex2D));


}

void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate)

{
	LPDIRECT3DDEVICE9 Direct3D_GetDevice();

	float w = Texture_GetWidth(texture_index);
	float h = Texture_GetHeight(texture_index);

	float w2 = Texture_GetWidth(texture_index)*rate;
	float h2 = Texture_GetHeight(texture_index)*rate;

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[]
	{
		{ D3DXVECTOR4(dx	,dy			,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0		,v0) },
		{ D3DXVECTOR4(dx + tw	,dy			,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0 + u1	,v0) },
		{ D3DXVECTOR4(dx	,dy + th		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0		,v0 + v1) },
		{ D3DXVECTOR4(dx + tw	,dy + th		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0 + u1	,v0 + v1) },


	};


	//VRAMへの転送
	//仮想アドレス
	Vertex2D* pV;

	//頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();
	//転送終了


	//頂点バッファのロック
	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;
	pIndex[4] = 2;
	pIndex[5] = 1;
	g_pIndexBuffer->Unlock();


	Direct3D_GetDevice()->SetFVF(FVF_VERTEX2D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(texture_index));
	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);

	//Direct3D_GetDevice()->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,2, v, sizeof(Vertex2D));
	//Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v, sizeof(Vertex2D));

}

/*cx,cy  中心からどれくらい離れているか
void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rotation)
{
LPDIRECT3DDEVICE9 Direct3D_GetDevice();

float w = Texture_GetWidth(texture_index);
float h = Texture_GetHeight(texture_index);

float px[4], py[4];

float u0 = (float)tx / w;
float v0 = (float)ty / h;
float u1 = (float)tw / w;
float v1 = (float)th / h;

px[0] =	dx*cos(rotation) - dy*sin(rotation);
py[0] =	dx*sin(rotation) + dy*cos(rotation);
px[1] =	(dx + tw)*cos(rotation) - dy*sin(rotation);
py[1] =	(dx + tw)*sin(rotation) + dy*cos(rotation);
px[2] =	dx*cos(rotation) - (dy + th)*sin(rotation);
py[2] =	dx*sin(rotation) + (dy + th)*cos(rotation);
px[3] =	(dx + tw)*cos(rotation) - (dy + th)*sin(rotation);
py[3] =	(dx + tw)*sin(rotation) + (dy + th)*cos(rotation);


Vertex2D v[]
{
{ D3DXVECTOR4(px[0] - 0.5f,py[0] - 0.5f		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0		,v0) },
{ D3DXVECTOR4(px[1] - 0.5f,py[1] - 0.5f		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0 + u1,v0) },
{ D3DXVECTOR4(px[2] - 0.5f,py[2] - 0.5f		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0		,v0 + v1) },
{ D3DXVECTOR4(px[3] - 0.5f,py[3] - 0.5f		,1.0f,1.0f)	,g_Color	,D3DXVECTOR2(u0 + u1,v0 + v1) },


};
Direct3D_GetDevice()->SetFVF(FVF_VERTEX2D);
Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(texture_index));
Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);

Direct3D_GetDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

}*/
void Sprite_Draw(int texture_index, float dx, float dy, int tx, int ty, int tw, int th, float cx, float cy, float sx, float sy, float rotation)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	float w = Texture_GetWidth(texture_index);
	float h = Texture_GetHeight(texture_index);

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)(tw + tx) / w;
	float v1 = (float)(th + ty) / h;

	float px[4], py[4];
	px[0] = -cx * sx * cos(rotation) - -cy * sy * sin(rotation);
	py[0] = -cx * sx * sin(rotation) + -cy * sy * cos(rotation);
	px[1] = (-cx + tw) * sx * cos(rotation) - -cy * sy * sin(rotation);
	py[1] = (-cx + tw) * sx * sin(rotation) + -cy * sy * cos(rotation);
	px[2] = -cx * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[2] = -cx * sx * sin(rotation) + (-cy + th) * sy * cos(rotation);
	px[3] = (-cx + tw) * sx * cos(rotation) - (-cy + th) * sy * sin(rotation);
	py[3] = (-cx + tw) * sx * sin(rotation) + (-cy + th) * sy * cos(rotation);

	Vertex2D v[] = {
		{ D3DXVECTOR4(px[0] + dx + cx - 0.5f,py[0] + dy + cy - 0.5f ,1.0f,1.0f), g_Color ,D3DXVECTOR2(u0 ,v0) },
		{ D3DXVECTOR4(px[1] + dx + cx - 0.5f,py[1] + dy + cy - 0.5f ,1.0f,1.0f), g_Color ,D3DXVECTOR2(u1 ,v0) },
		{ D3DXVECTOR4(px[2] + dx + cx - 0.5f,py[2] + dy + cy - 0.5f	,1.0f,1.0f), g_Color ,D3DXVECTOR2(u0 ,v1) },
		{ D3DXVECTOR4(px[3] + dx + cx - 0.5f,py[3] + dy + cy - 0.5f ,1.0f,1.0f), g_Color ,D3DXVECTOR2(u1 ,v1) },
	};

	pDevice->SetFVF(FVF_VERTEX2D);

	pDevice->SetTexture(0, Texture_GetTexture(texture_index));

	//ポリゴン書いて 158p						プリミティブ数,　ポリゴンデータ先頭アドレス,隣の頂点まで
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2D));	//低速簡単
}



void Sprite_Draw_exp(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate, float Xx, float Yy)
{
	LPDIRECT3DDEVICE9 Direct3D_GetDevice();

	float w = Texture_GetWidth(texture_index);
	float h = Texture_GetHeight(texture_index);

	float w2 = Texture_GetWidth(texture_index) / Xx*rate;
	float h2 = Texture_GetHeight(texture_index) / Yy*rate;

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[]
	{
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), g_Color, D3DXVECTOR2(u0,      v0) },
		{ D3DXVECTOR4(dx + w2, dy,      1.0f, 1.0f), g_Color, D3DXVECTOR2(u0 + u1, v0) },
		{ D3DXVECTOR4(dx,      dy + h2, 1.0f, 1.0f), g_Color, D3DXVECTOR2(u0,      v0 + v1) },
		{ D3DXVECTOR4(dx + w2, dy + h2, 1.0f, 1.0f), g_Color, D3DXVECTOR2(u0 + u1, v0 + v1) },


	};


	//VRAMへの転送
	//仮想アドレス
	Vertex2D* pV;

	//頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();
	//転送終了


	//頂点バッファのロック
	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;
	pIndex[4] = 2;
	pIndex[5] = 1;
	g_pIndexBuffer->Unlock();


	Direct3D_GetDevice()->SetFVF(FVF_VERTEX2D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(texture_index));
	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);

	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v, sizeof(Vertex2D));
}
void Sprite_Draw_exp2(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate, int Xx, int Yy)
{
	LPDIRECT3DDEVICE9 Direct3D_GetDevice();

	float w = Texture_GetWidth(texture_index);
	float h = Texture_GetHeight(texture_index);

	float w2 = Texture_GetWidth(texture_index) / Xx*rate;
	float h2 = Texture_GetHeight(texture_index) / Yy*rate;

	float u0 = (float)tx / w;
	float v0 = (float)ty / h;
	float u1 = (float)tw / w;
	float v1 = (float)th / h;


	Vertex2D v[]
	{
		{ D3DXVECTOR4(dx,      dy,      1.0f, 1.0f), g_Color, D3DXVECTOR2(u0,      v0) },
		{ D3DXVECTOR4(dx + w2, dy,      1.0f, 1.0f), g_Color, D3DXVECTOR2(u0 + u1, v0) },
		{ D3DXVECTOR4(dx,      dy + h2, 1.0f, 1.0f), g_Color, D3DXVECTOR2(u0,      v0 + v1) },
		{ D3DXVECTOR4(dx + w2, dy + h2, 1.0f, 1.0f), g_Color, D3DXVECTOR2(u0 + u1, v0 + v1) },


	};


	//VRAMへの転送
	//仮想アドレス
	Vertex2D* pV;

	//頂点バッファのロック
	g_pVertexBuffer->Lock(0, 0, (void**)&pV, 0);
	memcpy(pV, v, sizeof(v));
	g_pVertexBuffer->Unlock();
	//転送終了


	//頂点バッファのロック
	WORD* pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, 0);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 3;
	pIndex[4] = 2;
	pIndex[5] = 1;
	g_pIndexBuffer->Unlock();


	Direct3D_GetDevice()->SetFVF(FVF_VERTEX2D);
	Direct3D_GetDevice()->SetTexture(0, Texture_GetTexture(texture_index));
	Direct3D_GetDevice()->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(Vertex2D));
	Direct3D_GetDevice()->SetIndices(g_pIndexBuffer);

	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &v, sizeof(Vertex2D));
}