#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"debug_primitive.h"
#include"common.h"
#include"CubeMove.h"
#include"texture.h"
#include"sprite.h"
#include"Light.h"
#include"Camera.h"
#include "Model.h"
#include"heri.h"
#include"input.h"
#include"soukousya.h"
#include"bullet.h"
#include"SphereCollision.h"
#include"Dummy.h"
#include"wall.h"
#include"wall_factory.h"
#include"character.h"
#include"fade.h"
#include"scene.h"
#include"score.h"

int timer, sl1, time_count;

static bool g_bEnd=false;


void Hud_Init(void)
{
	timer = 0;
	sl1 = 0; 
	time_count = 0;
}

void Hud_Uninit(void)
{

}

void Hud_Update(void)
{
	time_count++;
	if (time_count >= 60)
	{
		sl1++;
		time_count = 0;
	}

	timer = 60 - sl1;
}

void Hud_Draw()
{
	Score_Draw3(200,200,timer,2,true,true);
}

