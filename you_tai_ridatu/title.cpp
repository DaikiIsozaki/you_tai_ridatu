#include"input.h"
#include"common.h"
#include"scene.h"
#include"fade.h"
#include<d3d9.h>
#include"sprite.h"
#include"texture.h"
#include"result.h"
#include"billboard.h"
#include"sound.h"


static bool g_bEnd=false;
static int alpha = 255;


void title_Initialize(void)
{
	PlaySound(SOUND_LABEL_TITLE);
	g_bEnd = false;

}
void title_Finalize(void)
{
	StopSound(SOUND_LABEL_TITLE);
}
void title_Update(void)
{
	
	if (!g_bEnd)
	{
		if (Keyboard_IsTrigger(DIK_LSHIFT))
		{
			fade_Start(true, 200, D3DCOLOR_RGBA(0, 0, 0, 0));
			alpha -= 1;
		}
	}

	if (Fade_Alpha() == 1.0f)
		{
			scene_Change(SCENE_INDEX_GAME);
		}

}
void title_Draw(void)
{
	Sprite_Draw(32, 0, 0, 1);
}

bool Title_bEnd(void)
{
	return g_bEnd;
}
