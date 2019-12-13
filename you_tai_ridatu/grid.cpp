#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include"Light.h"
#include"Camera.h"

//頂点構造体
typedef struct GridVertex3D_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
	//D3DXVECTOR2 texcoord;…入れない
}GridVertex3D;

#define FVF_GRIDVERTEX3D2D	(D3DFVF_XYZ| D3DFVF_DIFFUSE)//FVFの定義

//グローバル変数

static GridVertex3D v[44];

void Grid_Init(void)
{
	int b = 1;
	
	for (int a = -5; a < 6; a++, b++)
	{
		v[a + b + 4].position = D3DXVECTOR3(0.0f + a, 0.0f, 0.0f + 5);
		v[a + b + 4].color = D3DCOLOR_RGBA(255, 255, 0, 255);
		v[a + b + 5].position = D3DXVECTOR3(0.0f + a, 0.0f, 0.0f - 5);
		v[a + b + 5].color = D3DCOLOR_RGBA(255, 255, 0, 255);
	}

	int d = 1;

	for (int c = -5; c < 6; c++, d++)
	{
		v[c + d + 26].position = D3DXVECTOR3(0.0f + 5, 0.0f, 0.0f + c);
		v[c + d + 26].color = D3DCOLOR_RGBA(255, 255, 0, 255);
		v[c + d + 27].position = D3DXVECTOR3(0.0f - 5, 0.0f, 0.0f + c);
		v[c + d + 27].color = D3DCOLOR_RGBA(255, 255, 0, 255);
	}

	
}

void Grid_Uninit(void)
{

}

void Grid_Draw(void)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする


	//ワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorld;
	//(4*4)

	D3DXMatrixIdentity(&mtxWorld);//単位行列を作る
	
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);//ワールド変換行列

	
	Direct3D_GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	Direct3D_GetDevice()->SetFVF(FVF_GRIDVERTEX3D2D);
	Direct3D_GetDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 22, v, sizeof(GridVertex3D));
}