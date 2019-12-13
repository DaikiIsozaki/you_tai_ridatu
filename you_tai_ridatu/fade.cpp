#include<d3d9.h>
#include"direct3d.h"
#include"sprite.h"
#include"common.h"

#define FVF_FADE_VERTEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

static D3DXCOLOR g_Fadecolor(0.0f, 0.0f, 0.0f, 1.0f);
static float g_Alpha = 0.0f;	//alphaの値
static float g_AddAlpha = 0.0f;	//増やす値
static bool g_bOut = false;		//フェードインかアウトか
static bool g_bIsFade = false;	//フェード中かどうか

typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}FadeVertex;

void fade_Initialize(void)
{
	g_Alpha = 0.0f;
	g_AddAlpha = 0.0f;
	g_bOut = false;
	g_bIsFade = false;
}
void fade_Finalize(void)
{

}
void fade_Update(void)
{
	if (!g_bIsFade)
	{
		return;
	}

	
	g_Alpha += g_AddAlpha;
	
	
	if (g_bOut)
	{
		if (g_Alpha >= 1.0f)
		{
			
			g_bIsFade = false;
			g_Alpha = 1.0f;
		}
	}
	if(!g_bOut)
	{
		if (g_Alpha <= 0.0f)
		{
			
			g_bIsFade =true;
			g_Alpha = 0.0f;
		}
	}
}
void fade_Draw(void)
{
	if (g_Alpha <= 0.000000000000000001f)
	{
		return;
	}

	g_Fadecolor.a = g_Alpha;

	FadeVertex v[] =
	{
		{ D3DXVECTOR4(0.0f,0.0f,1.0f,1.0f),					g_Fadecolor },
		{ D3DXVECTOR4(SCREEN_WIDTH,0.0f,1.0f,1.0f),			g_Fadecolor },
		{ D3DXVECTOR4(0.0f,SCREEN_HEIGHT,1.0f,1.0f),			g_Fadecolor },
		{ D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,1.0f,1.0f),	g_Fadecolor },
	};

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	pDevice->SetFVF(FVF_FADE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));


}

void fade_Start(bool bOut, float frame, D3DCOLOR color)
{
	g_bIsFade = true;
	g_bOut = bOut;
	g_AddAlpha = 1.0f / frame;
	g_Fadecolor = color;
	

	if (g_bOut)
	{

		g_Alpha = 0.0f;
		
	}
	if(!g_bOut)
	{
		
		g_Alpha = 1.0f;
		g_AddAlpha = -g_AddAlpha;
	}
}

bool Fade_IsFade(void)
{
	return g_bIsFade;
}

float Fade_Alpha(void)
{
	return g_Alpha;
}

