#include"direct3d.h"
#include"common.h"

void Light_Init(void)
{

}

void Light_Set(void)
{
	
	Direct3D_GetDevice()->SetRenderState(D3DRS_LIGHTING, TRUE);
	D3DLIGHT9 light;
	ZeroMemory(&light, sizeof(light));
	light.Type = D3DLIGHT_DIRECTIONAL;//平行光源
	D3DXVECTOR3 vecDirLight(0.0f, -1.0f, -1.0f);//ライトベクトル
	D3DXVec3Normalize(&vecDirLight, &vecDirLight);
	light.Direction = vecDirLight;
	light.Diffuse.r = 1.0f;//-|
	light.Diffuse.g = 1.0f;// |->ライト色
	light.Diffuse.b = 1.0f;// |　(ディフューズ)
	light.Diffuse.a = 1.0f;//-|
	Direct3D_GetDevice()->SetLight(0, &light);
	Direct3D_GetDevice()->LightEnable(0, TRUE);
	Direct3D_GetDevice()->SetRenderState(D3DRS_DIFFUSEMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする
	
	Direct3D_GetDevice()->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);//法線を1に固定する(拡大縮小用)

	//アンビエント
	Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_RGBA(100, 100, 100, 255));
	//Direct3D_GetDevice()->SetRenderState(D3DRS_AMBIENTMATERIALSOURCE, D3DMCS_COLOR1);//頂点カラーをマテリアルカラーにする
	

}
