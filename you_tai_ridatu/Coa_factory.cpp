#include"common.h"
#include"Enemy.h"
#include"Coa.h"
#include"wall.h"


typedef struct CoaFactory_tag
{
	float x, y, z;
	int frame;
}cFactory;

static const cFactory g_cF[] = {
	{ -33.0f,0.0f,-9.0f,NULL},
	{ -19.0f,0.0f,-25.0f,NULL },
	{ -20.0f,0.0f,-36.0f,NULL },
	{ 10.0f,0.0f,-4.0f,NULL },
	{ 24.0f,0.0f,-25.0f,NULL },

};

static int g_FrameCount = 0;
static int g_Index = 0;

void CoaFactory_Initialize(void)
{
	g_FrameCount = 0;
	g_Index = 0;
}

void CoaFactory_Update(void)
{
	for (;;)
	{
		if (g_cF[g_Index].frame < 0)
		{
			break;
		}
		else if (g_cF[g_Index].frame <= g_FrameCount)
		{
			Coa_Create(g_cF[g_Index].x, g_cF[g_Index].y, g_cF[g_Index].z);
			g_Index++;
		}
		else
		{
			break;
		}
	}
	g_FrameCount++;
}