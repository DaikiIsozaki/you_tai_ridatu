#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"
#include"Model.h"

LPD3DXMESH g_pD3DXMesh[INDEX_MODEL_MAX];//メッシュを受け取る変数
//LPD3DXBUFFER pD3DXAdjacencyBuffer;	//隣接性情報を受け取る変数
DWORD g_dwNumMaterials[INDEX_MODEL_MAX];//マテリアル総数	DrawSubsetを呼ぶ回数
LPD3DXBUFFER g_pD3DXMtrlBuffer;			//マテリアル情報を受け取る変数

LPDIRECT3DTEXTURE9 *g_pTextures[INDEX_MODEL_MAX];
D3DMATERIAL9 *g_pMaterial[INDEX_MODEL_MAX];
LPD3DXBUFFER MaterialBuffer[INDEX_MODEL_MAX];	//マテリアル情報を受け取る変数

// 読み込みテクスチャ情報
static const MaterialFile fileData[] = {
	"asset/Model/heri_hontai.blend.x",
	"asset/Model/heri_puropera.blend.x",
	"asset/Model/dish.blend.x",
	"asset/Model/CoffeeCup_Blue.blend.x",
	"asset/Model/CoffeeCup_midori.blend.x",
	"asset/Model/CoffeeCup_kiiro.blend.x",
	"asset/Model/suraimu3.blend.x",
	"asset/Model/gaitou3.blend.x",
	"asset/Model/benti2.blend.x",
	"asset/Model/justaway_head.blend.x",
	"asset/Model/justaway_body.blend.x",
	"asset/Model/justaway_LeftArm.blend.x",
	"asset/Model/justaway_RightArm.blend.x",
	"asset/Model/trampoline_main.x",
	"asset/Model/soukousyaV2_body.blend.x",
	"asset/Model/soukousyaV2_Sya-shi.blend.x",
	"asset/Model/soukousyaV2_Taiya.blend.x",
	"asset/Model/soukousyaV2_Taiya2.blend.x",
	"asset/Model/soukousyaV2_Taiya3.blend.x",
	"asset/Model/soukousyaV2_Taiya4.blend.x",
	"asset/Model/soukousyaV2_kiju_dodai.blend.x",
	"asset/Model/soukousyaV2_kiju.blend.x",
	"asset/Model/soukousya1_body.blend.x",
	"asset/Model/soukousya1_houdai.blend.x",
	"asset/Model/soukousya1_houdai_dodai.blend.x",
	"asset/Model/soukousya1_kiju.blend.x",
	"asset/Model/soukousya1_taiya.blend.x",
	"asset/Model/maru.blend.x",
	"asset/Model/entyu.blend.x",
	"asset/Model/tyouhoukei.blend.x",
	"asset/Model/hana.blend.x",
	"asset/Model/yu-rei.blend.x",
	"asset/Model/test.blend.x",
	"asset/Model/wall.blend.x",
	
	"asset/Model/Chara_head.blend.x",
	"asset/Model/Chara_body.blend.x",
	"asset/Model/Chara_hand.blend.x",
	"asset/Model/Chara_leg.blend.x",

	"asset/Model/Enemy_head.blend.x",
	"asset/Model/Enemy_body.blend.x",
	"asset/Model/Enemy_hand.blend.x",
	"asset/Model/Enemy_leg.blend.x",
	"asset/Model/Enemy_coa.blend.x",

};

void Model_Xfile_Load(int index)
{
	HRESULT hr;
	hr = D3DXLoadMeshFromX(fileData[index].filename, D3DXMESH_MANAGED || D3DXMESH_WRITEONLY, Direct3D_GetDevice(), NULL, &g_pD3DXMtrlBuffer, NULL, &g_dwNumMaterials[index], &g_pD3DXMesh[index]);

	g_pTextures[index] = new LPDIRECT3DTEXTURE9[g_dwNumMaterials[index]];
	g_pMaterial[index] = new D3DMATERIAL9[g_dwNumMaterials[index]];

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)g_pD3DXMtrlBuffer->GetBufferPointer();

	for (int i = 0;i < g_dwNumMaterials[index];i++)
	{
		g_pMaterial[index][i] = d3dxMaterials[i].MatD3D;
		g_pMaterial[index][i].Ambient = g_pMaterial[index][i].Diffuse;
		//テクスチャーの読み込み
		if (d3dxMaterials[i].pTextureFilename == NULL)//テクスチャーを貼ってないマテリアル　ファイル名もなし
		{
			g_pTextures[index][i] = NULL;
		}
		else
		{
			HRESULT hr;
			hr = D3DXCreateTextureFromFile(Direct3D_GetDevice(), d3dxMaterials[i].pTextureFilename, &g_pTextures[index][i]);
		}
		if (FAILED(hr))
		{
			g_pTextures[i] = NULL;		//テクスチャなし
			MessageBox(NULL, "マテリアルが読み込まれてないよ", "エラー", MB_OK);
		}
	}
}



void Model_Draw(int index)
{
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_MATERIAL);
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_MATERIAL);

	//ワールド変換行列のセット
	for (int i = 0;i < g_dwNumMaterials[index];i++)
	{
		Direct3D_GetDevice()->SetMaterial(&g_pMaterial[index][i]);
		Direct3D_GetDevice()->SetTexture(0, g_pTextures[index][i]);
		g_pD3DXMesh[index]->DrawSubset(i);
	}

	//ワールド座標変換行列の作成と設定
	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);//単位行列を作る		
}

void Model_Finalise(int index)
{
	if (g_pD3DXMesh[index] != NULL)
	{
		g_pD3DXMesh[index]->Release();
	}
	if (g_pD3DXMtrlBuffer != NULL)
	{
		g_pD3DXMtrlBuffer->Release();
	}
	delete[]g_pTextures[index];
	delete[]g_pMaterial[index];

}