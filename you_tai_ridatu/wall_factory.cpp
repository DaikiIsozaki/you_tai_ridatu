#include"common.h"
#include"wall.h"

typedef struct WallFactory_tag
{
	float x, y, z;
	int frame;
	int type;

}wFactory;

static const wFactory g_wF[] = {
	
	{-FIELD_X/2,0.0f,FIELD_Z/2 - 20.0f,0.0f,WALL_TYPE_1},
	{-FIELD_X/2+4.0f,0.0f,FIELD_Z/2 - 20.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0f,0.0f,FIELD_Z/2 - 20.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 12.0f,0.0f,FIELD_Z/2 - 20.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 12.0f,0.0f,FIELD_Z/2 - 24.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 12.0f,0.0f,FIELD_Z/2 - 26.0f,0.0f,WALL_TYPE_1 },

	
	{ -FIELD_X/2 + 12.0f,0.0f,FIELD_Z/2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0f,0.0f,FIELD_Z/2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0f,0.0f,FIELD_Z/2 - 42.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0f,0.0f,FIELD_Z/2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0f,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 4.0f,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 ,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0,0.0f,FIELD_Z/2 - 54.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X/2 + 16.0,0.0f,FIELD_Z/2 - 54.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 20.0,0.0f,FIELD_Z/2 - 54.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 20.0,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X/2 + 20.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 24.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 32.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },//
	{ -FIELD_X/2 + 20.0,0.0f,FIELD_Z/2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 16.0,0.0f,FIELD_Z/2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 12.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 12.0,0.0f,FIELD_Z/2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 8.0,0.0f,FIELD_Z/2- 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 4.0,0.0f,FIELD_Z/2- 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 20.0,0.0f,FIELD_Z/2 - 70.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 20.0,0.0f,FIELD_Z / 2 - 74.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 32.0,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 42.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 26.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 26.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 24.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 20.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 16.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 28.0,0.0f,FIELD_Z/2 - 12.0f,0.0f,WALL_TYPE_1 },

	
	{ -FIELD_X/2 + 36.0,0.0f,FIELD_Z/2 - 16.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 16.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X/2 + 40.0,0.0f,FIELD_Z/2 - 12.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 44.0,0.0f,FIELD_Z / 2 - 12.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 48.0,0.0f,FIELD_Z / 2 - 12.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 12.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 14.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 18.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 48.0,0.0f,FIELD_Z / 2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 56.0,0.0f,FIELD_Z / 2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 42.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 60.0,0.0f,FIELD_Z / 2 - 44.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 48.0,0.0f,FIELD_Z / 2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 44.0,0.0f,FIELD_Z / 2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 56.0,0.0f,FIELD_Z / 2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 54.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 58.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 60.0,0.0f,FIELD_Z / 2 - 58.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 56.0,0.0f,FIELD_Z / 2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 70.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0,0.0f,FIELD_Z / 2 - 74.0f,0.0f,WALL_TYPE_1 },



	//{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 72.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 14.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 18.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 22.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 26.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 42.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 54.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 58.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 70.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 74.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X / 2 - 4.0f,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },


	{ -FIELD_X / 2 ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2+4.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 8.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 12.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 16.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 20.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 24.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 28.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 32.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 36.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 40.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 44.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 48.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 56.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 60.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 10.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 14.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 18.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 22.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 26.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 30.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 34.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 38.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 42.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 46.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 50.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 54.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 58.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 62.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 66.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 70.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 74.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2 + 64.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2 + 60.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 56.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 52.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 48.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 44.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 40.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 36.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 32.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 28.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 24.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 20.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 16.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 12.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 8.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2 + 4.0f ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },
	{ -FIELD_X / 2		  ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },

	{ -FIELD_X / 2-4.0f		  ,0.0f,FIELD_Z / 2 - 78.0f,0.0f,WALL_TYPE_1 },

};

static int g_FrameCount = 0;
static int g_Index = 0;


void Wall_Factory_Initialize(void)
{
	g_FrameCount = 0;
	g_Index = 0;
}

void Wall_Factory_Update(void)
{
	for (;;)
	{
		if (g_wF[g_Index].frame < 0)
		{
			break;
		}
		else if (g_wF[g_Index].frame <= g_FrameCount)
		{
			Wall_Create(g_wF[g_Index].x, g_wF[g_Index].y, g_wF[g_Index].z, g_wF[g_Index].type);

			g_Index++;
		}
		else
		{
			break;
		}
	}
	g_FrameCount++;
}
