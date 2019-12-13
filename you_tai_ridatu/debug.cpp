#include"debug.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"common.h"
#include<stdio.h>
#include"character.h"


static LPD3DXFONT g_pD3DXFont = NULL;

void Debug_Initialize(void)
{

	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"Terminal",&g_pD3DXFont);
}
void Debug_Finalize(void)
{
#if defined(_DEBUG)||defined(DEBUG)
	if (g_pD3DXFont)
	{
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}

#endif	//_DEBUG||DEBUG

}
void Debug_Draw(void)
{

#if defined(_DEBUG)||defined(DEBUG)



	//RECT rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	//g_pD3DXFont->DrawText(NULL, , -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));

#endif	//_DEBUG||DEBUG
	RECT rect = { 360,10,SCREEN_WIDTH,SCREEN_HEIGHT };
	//g_pD3DXFont->DrawText(NULL, , -1, &rect, DT_LEFT, D3DCOLOR_RGBA(0, 255, 0, 255));
	//wakarann
	
}