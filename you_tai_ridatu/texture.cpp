#include<Windows.h>
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"sprite.h"

#define TEXTURE_FILENAME_MAX	(64)

typedef struct TextureFile_tag
{
	const char filename[TEXTURE_FILENAME_MAX];
	int width;
	int height;

}TextureFileData;

static const TextureFileData TEXTURE_FILES[] =
{
	{ "asset/texture/witch3.png",128,128 },//("‰æ‘œ‚Ì‚ ‚é‚Æ‚±‚ë",‰æ‘œ‚Ì‘å‚«‚³,‰æ‘œ‚Ì‘å‚«‚³  0
	{ "asset/texture/namai2.png",100,100  },//1
	{ "asset/texture/bullet.png",100,100 },//2
	{ "asset/texture/exp.png",128,128 },//3
	{ "asset/texture/number.tga",320,32 },//4
	{ "asset/texture/bakuhatu1.png",168,100 },//5
	{ "asset/texture/Heishi.png",300,300 },//6
	{ "asset/texture/anim.jpg",300,300 },//7
	{ "asset/texture/neko.jpg",182,492 },//8
	{ "asset/texture/effect000.jpg",80,80 },//9
	{ "asset/texture/sangoku.jpg",121,104 },//10
	{ "asset/texture/war_dragoon_ryuukihei.png",336,400 },//11
	{ "asset/texture/title1.jpg",1024,576 },//12
	{ "asset/texture/result_gameclear.jpg",1024,576 },//13
	{ "asset/texture/result_gameover.jpg",1024,576 },//14
	{ "asset/texture/Number.jpg",900,605 },//15
	{ "asset/texture/haikei2.jpg",1024,576 },//16
	{ "asset/texture/hud.png",343,342 },//17
	{ "asset/texture/number2.png",320,32 },//18
	{ "asset/texture/reload2.png",343,342 },//19
	{ "asset/texture/heart.png",100,100 },//20
	{ "asset/texture/Bom.png",100,100 },//21
	{ "asset/texture/bill.jpg",50,50 },//22
	{ "asset/texture/tex.png",1024,1024 },//23
	{ "asset/texture/bullet000.png",80,80 },//24
	{ "asset/texture/kuroshikaku.png",400,400 },//25
	{ "asset/texture/field004.jpg",320,320},//26
	{ "asset/texture/haikei4.png",400,400 },//27
	{ "asset/texture/justaway.png",640,400 },//28
	{ "asset/texture/explosion000.png",640,80 },//29
	{ "asset/texture/Bullet1.png",30,30 },//30
	{ "asset/texture/shadow000.jpg",80,80 },//31
	{ "asset/texture/TITLE2.png",500,300 },//32
	{ "asset/texture/Result.png",500,300 },//33
	
};

static const int TEXTURE_MAX = ARRAYSIZE(TEXTURE_FILES);
static LPDIRECT3DTEXTURE9 g_pTextures[TEXTURE_MAX];


int Texture_Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	HRESULT hr;
	int failed_count = 0;

	for (int i = 0;i < TEXTURE_MAX;i++)
	{
		hr = D3DXCreateTextureFromFile(pDevice, TEXTURE_FILES[i].filename, &g_pTextures[i]);
		if (FAILED(hr))
		{
			failed_count++;
		}
	}

	return failed_count;
}

void Texture_Release(void)
{
	for (int i = 0;i < TEXTURE_MAX;i++)
	{
		if (g_pTextures[i])
		{
			g_pTextures[i]->Release();
			g_pTextures[i] = NULL;
		}
	}
}

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index)
{
	return g_pTextures[index];
}

int Texture_GetWidth(int index)
{
	return TEXTURE_FILES[index].width;
}
int Texture_GetHeight(int index)
{
	return TEXTURE_FILES[index].height;
}