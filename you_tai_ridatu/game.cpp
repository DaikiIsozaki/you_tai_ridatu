#include<Windows.h>
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"sprite.h"
#include"game.h"
#include"Cube.h"
#include"grid.h"
#include"CubeMove.h"
#include"Light.h"
#include"Camera.h"
#include"Model.h"
#include"billboard.h"
#include"MeshField.h"
#include"CoffeeCup.h"
#include"heri.h"
#include"Komono.h"
#include"justaway.h"
#include"soukousya.h"
#include"billboard.h"
#include"bullet.h"
#include"exp.h"
#include"character.h"
#include"Dummy.h"
#include"input.h"
#include"debug.h"
#include"Enemy.h"
#include"SphereCollision.h"
#include"EnemyFactory.h"
#include"wall.h"
#include"wall_factory.h"
#include"HUD.h"
#include"shadow.h"
#include"Coa.h"
#include"Coa_factory.h"
#include"fade.h"
#include"title.h"
#include"HUD.h"
#include"sound.h"

int A;
static bool g_Gend;
static int fade_Alpha = 255;
bool fade_OK = false;


void Game_Initialize(void)
{
	Grid_Init();
	Cube_Init();
	BB_Init();
	CubeMove_Init();
	Light_Init();
	Camera_Init();
	MeshField_Init(1.0f, FIELD_X+10.0f, FIELD_Z + 10.0f);
	MeshCylinder_Init(1.0f,70.0f,360,10);
	MeshSkydome_Init(50.0f,70.0f,40,10);
	CC_Init();
	Heri_Init();
	Komono_Init();
	Justaway_Init();
	Soukousya_Init();
	Bullet_Init();
	Exp_Init();
	Character_Init();
	Dummy_Init();
	Debug_Initialize();
	Enemy_Init();
	EnemyFactory_Initialize();
	Wall_Init();
	Wall_Factory_Initialize();
	Hud_Init();
	Shadow_Initialize();
	Coa_Init();
	CoaFactory_Initialize();
	Hud_Init();
	PlaySound(SOUND_LABEL_BGM);
	A = 0;
	g_Gend = false;
}

void Game_Finalize(void)
{
	StopSound(SOUND_LABEL_BGM);
	Cube_Uninit();
	BB_Uninit();
	MeshField_Uninit();
	CC_Uninit();
	Character_Uninit();
	Dummy_Uninit();
	Debug_Finalize();
	Enemy_Uninit();
	Wall_Uninit();
	Hud_Uninit();
	Shadow_Finalize();
	Coa_Uninit();
	Hud_Uninit();
}

void Game_Update(void)
{
	if (Fade_Alpha() == 1.0f)
	{
		fade_Start(false, 200, D3DCOLOR_RGBA(0, 0, 0, 0));
		

	}

	switch (A)
	{
	case 0:
		if (Keyboard_IsTrigger(DIK_RETURN))
		{
			A = 1;

		}
		break;

	case 1://A=1
		if (Keyboard_IsTrigger(DIK_RETURN))
		{
			A = 2;
		}
		break;
	case 2://A=2
		if (Keyboard_IsTrigger(DIK_RETURN))
		{
			A = 1;
		}
		break;
	}
	Camera_Update(A);
	Hud_Update();
	
	Character_Update(A);
	Shadow_Update();
	Dummy_Update(A);
	Bullet_Update();
	Exp_Update();

	EnemyFactory_Update();

	Wall_Factory_Update();

	CoaFactory_Update();
	
	Enemy_Update(A);
	Coa_Update(A);

	Wall_Update();
	Hud_Update();
	
	AtariHantei_Enemy();
	AtariHantei_Wall();
	AtariHantei_Gost(A);

	Scene_Change();
	
	
}

void Game_Draw(void)
{
	if (Fade_Alpha()==0.0f)
	{
		Character_Body_Draw();
		Enemy_body_Draw();
		Coa_Draw();
		Light_Set();//1î‘è„Ç…Ç∑ÇÈ
		Debug_Draw();

		MeshField_Draw(0);
		MeshField_Draw(1);
		//	MeshField_Draw(2);


		Wall_Draw();

		Dummy_Draw(0.0f, 1.0f, 0.0f, A);


		Bullet_Draw();
		Exp_Draw();
		Shadow_Draw();
		Hud_Draw();
	}
	
	
}

