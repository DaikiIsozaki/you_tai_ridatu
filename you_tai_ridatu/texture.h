#ifndef TEXTURE_H
#define TEXTURE_H



#include<Windows.h>
#include<d3dx9.h>
#include<d3dx9.h>


int Texture_Load(void);

void Texture_Release(void);

LPDIRECT3DTEXTURE9 Texture_GetTexture(int index);

int Texture_GetWidth(int index);
int Texture_GetHeight(int index);



enum
{
	TEXTURE_INDEX_KOBENI,
	TEXTURE_INDEX_RUN,
	TEXTURE_INDEX_KOBENi2,
};

#endif //!TEXTURE_H