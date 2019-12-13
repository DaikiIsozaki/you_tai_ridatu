#include"scene.h"
#include"title.h"
#include"game.h"
#include"result.h"

static SCENE_INDEX g_SceneIndex;
static SCENE_INDEX g_SceneNextIndex;

typedef void(*SceneFunc)(void);//ä÷êîÉ|ÉCÉìÉ^å^

static const SceneFunc Initialize[] = {
	title_Initialize,
	Game_Initialize,
	result_Initialize,
};


void scene_Initialize(SCENE_INDEX index)
{
	g_SceneNextIndex = g_SceneIndex = index;

	Initialize[g_SceneIndex]();
	
}
void scene_Finalize(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITLE:
		title_Finalize();
		break;
	case SCENE_INDEX_GAME:
		Game_Finalize();
		break;
	case SCENE_INDEX_Result:
		result_Finalize();
		break;

	}
}
void scene_Update(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITLE:
		title_Update();
		break;
	case SCENE_INDEX_GAME:
		Game_Update();
		break;
	case SCENE_INDEX_Result:
		result_Update();
		break;

	}
}
void scene_Draw(void)
{
	switch (g_SceneIndex)
	{
	case SCENE_INDEX_TITLE:
		title_Draw();
		break;
	case SCENE_INDEX_GAME:
		Game_Draw();
		break;
	case SCENE_INDEX_Result:
		result_Draw();
		break;

	}
}
void scene_Check(void)
{
	if (g_SceneIndex != g_SceneNextIndex)
	{
		scene_Finalize();
		scene_Initialize(g_SceneNextIndex);
	}
}
void scene_Change(SCENE_INDEX index)
{
	g_SceneNextIndex = index;
}