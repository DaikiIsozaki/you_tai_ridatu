#include"common.h"
#include"Enemy.h"
#include"Coa.h"
#include"wall.h"


typedef struct EnemyFactory_tag
{
	float x, y,z;
	int frame;
	int type;
	float Ang;
}eFactory;

static const eFactory g_eF[] = {
	{-33.0f,0.0f,10.0f,NULL ,ENEMY_TYPE_TEST ,180.0f},
	{-2.0f,0.0f,-8.0f,NULL ,ENEMY_TYPE_TEST ,-90.0f},
	{-12.0f,0.0f,-34.0f,NULL,ENEMY_TYPE_TEST,90.0f},
	{20.0f,0.0f,22.0f,NULL,ENEMY_TYPE_TEST,180.0f },


};



static int g_FrameCount = 0;
static int g_Index = 0;

void EnemyFactory_Initialize(void)
{
	g_FrameCount = 0;
	g_Index = 0;

}

void EnemyFactory_Update(void)
{
	for (;;)
	{
		if (g_eF[g_Index].frame < 0)
		{
			break;
		}
		else if (g_eF[g_Index].frame <= g_FrameCount)
		{
			Enemy_Create(g_eF[g_Index].x, g_eF[g_Index].y,g_eF[g_Index].z,g_eF[g_Index].type,g_eF[g_Index].Ang);
			g_Index++;
		}
		else
		{
			break;
		}
	}
	g_FrameCount++;

}
