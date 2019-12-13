#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include "bullet.h"
#include "BillBoard.h"
//#include "enemy.h"
//#include "judgement.h"

#define EXP_SIZE (25.0f)
#define MAX_EFFECT (256)
#define EFFECT_WAIT (4)	

int exp_counter;
int ex_flg;
float exp_u;
float exp_v;
float expX;
float expY;
float x;
float y;


typedef struct{
	D3DXVECTOR3 Exp_position;
//	int e_start;
	float puttern;
	int Effect_counter;
	bool eflg;
}EFFECT;

EFFECT g_effect[MAX_EFFECT];
int g_count;		//現在の時間

void Exp_Init(void)
{
	exp_counter = 0;
	exp_u = 0.0f;
	exp_v = 0.0f;
	ex_flg = 0;
	

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].Exp_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		//g_effect[i].e_start = 0;
		g_effect[i].puttern = 0;
		g_effect[i].Effect_counter = 0;
		g_effect[i].eflg = false;
	}
	g_count = 0;
}



void Exp_Uninit(void)
{

}



void Exp_Update(void)
{
	
	g_count++;
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].eflg == true)
		{

			//爆発アニメーション
			if (g_effect[i].Effect_counter >= 800)
			{
				g_effect[i].eflg = false;
				g_effect[i].Effect_counter = 0;
			}
			g_effect[i].Effect_counter++;


			if (g_effect[i].Effect_counter % 100 == 0)
			{
				if (g_effect[i].puttern > 1.0f)
				{
					g_effect[i].puttern = 0;
				}
				g_effect[i].puttern += 1.0f / 8;
				
			}
			
			

		/*	g_effect[i].puttern = (g_count - g_effect[i].e_start) / EFFECT_WAIT;
			if (g_effect[i].puttern >= 8)
			{
				g_effect[i].eflg = false;
			}*/
		}
	}



	
}




void Exp_Draw(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].eflg == true)
		{
			BB_Exp_Draw(g_effect[i].Exp_position.x, g_effect[i].Exp_position.y, g_effect[i].Exp_position.z + 5.0f, g_effect[i].puttern,29);
			//Sprite_SetColor(D3DCOLOR_RGBA(255, 255, 255, 255));
			//Sprite_Draw_exp2(3, g_effect[i].eX, g_effect[i].eY, put_x * 64, put_y * 64, 64, 64);

		}
	}

}



void Exp_Create(float Ex, float Ey, float z)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].eflg == false)
		{
			g_effect[i].Exp_position.x = Ex;
			g_effect[i].Exp_position.y = Ey;
			g_effect[i].Exp_position.z = z;
										 
			//g_effect[i].e_start = g_count;	//エフェクト開始時刻

			//爆発を有効にする
			g_effect[i].eflg = true;
			return;
		}
	}
	


}

void Effect_Destroy(int i)
{
	//爆発を無効にする
	g_effect[i].eflg = false;
}

bool Effect_IsEnable(int i)
{
	return g_effect[i].eflg;
}