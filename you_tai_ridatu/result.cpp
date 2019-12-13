#include"input.h"
#include"common.h"
#include"game.h"
#include"scene.h"
#include"fade.h"
#include<d3d9.h>
#include"sprite.h"
#include"texture.h"
#include"sound.h"

static bool g_bResult;

void result_Initialize(void)
{
	PlaySound(SOUND_LABEL_RESULT);
	g_bResult = false;
}
void result_Finalize(void)
{
	StopSound(SOUND_LABEL_RESULT);
}
void result_Update(void)
{
	if (Keyboard_IsTrigger(DIK_LSHIFT))
	{
		scene_Change(SCENE_INDEX_TITLE);
	}
}
void result_Draw(void)
{
	Sprite_Draw(33, 0, 0,  0);
}

bool bResult(void)
{
	return g_bResult;
}