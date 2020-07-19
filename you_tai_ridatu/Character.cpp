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
#include"HUD.h"
#include"shadow.h"

#define CHARACTERSPEED	(0.01f)
#define X_RIMT			(30.0f)
#define Z_RIMT			(30.0f)
#define HIT_RADIUS		(1.0f)

D3DXVECTOR3 Character;
D3DXVECTOR3 Keep_Character;
D3DXVECTOR3 Front;
D3DXVECTOR3 Right;
D3DXVECTOR3 Up;

D3DXMATRIX g_Save_MatrixCharacter;

float CharaAng;
float Chara_Ang;
bool hand_pluss;
bool leg_pluss;
bool Flag = false;
bool Move_flag;

static int cnt2 = 0;


PLAYER Player;

void Character_Init(void)
{
	Model_Xfile_Load(INDEX_MODEL_CHARA_HEAD);
	Model_Xfile_Load(INDEX_MODEL_CHARA_BODY);
	Model_Xfile_Load(INDEX_MODEL_CHARA_HAND);
	Model_Xfile_Load(INDEX_MODEL_CHARA_LEG);

	

	Character = D3DXVECTOR3(-31.0f, 0.0f, 22.0f);
	Keep_Character =D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	Front = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	Up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXVec3Cross(&Right, &Front, &Up);
	D3DXVec3Normalize(&Right, &Right);
	D3DXVec3Cross(&Up, &Right, &Front);
	D3DXVec3Normalize(&Up, &Up);
	D3DXVec3Normalize(&Front, &Front);
	CharaAng = 0.0f;
	Chara_Ang = 0.0f;

	Character_Create(-31.0f, 0.0f, 22.0f);


	Player.HP = PLAYER_HP;
	Player.shadow_number = 0;
	hand_pluss=true;
	leg_pluss=true;
	Move_flag = false;

	Player.Collision.CenterPosition= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void Character_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_CHARA_HEAD);
	Model_Finalise(INDEX_MODEL_CHARA_BODY);
	Model_Finalise(INDEX_MODEL_CHARA_HAND);
	Model_Finalise(INDEX_MODEL_CHARA_LEG);
	
}

void Character_Update(int Case)
{
	//移動
	

	D3DXVECTOR3 f(Front);
	if (Case == 0 || Case == 2)
	{

		if (Keyboard_IsPress(DIK_W))
		{
			f.y = 0.0f;
			Character += f * CHARACTERSPEED;

			
		}
		if (Keyboard_IsPress(DIK_S))
		{
			f.y = 0.0f;
			Character -= f * CHARACTERSPEED;

		}

		if (Keyboard_IsPress(DIK_A))
		{

			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.5f));
			D3DXVec3TransformNormal(&Front, &Front, &mtxR);
			D3DXVec3TransformNormal(&Right, &Right, &mtxR);
			D3DXVec3TransformNormal(&Up, &Up, &mtxR);
			CharaAng -= 0.5f;

		}
		if (Keyboard_IsPress(DIK_D))
		{
			D3DXMATRIX mtxR;
			D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.5f));
			D3DXVec3TransformNormal(&Front, &Front, &mtxR);
			D3DXVec3TransformNormal(&Right, &Right, &mtxR);
			D3DXVec3TransformNormal(&Up, &Up, &mtxR);
			CharaAng += 0.5f;
		}

		if (hand_pluss)
		{
			Chara_Ang += 0.1f;
			if (Chara_Ang > 45.0f)
			{
				hand_pluss = false;
			}
		}

		if (!hand_pluss)
		{
			Chara_Ang -= 0.1f;
			if (Chara_Ang < -45.0f)
			{
				hand_pluss = true;
			}
		}

	/*	if (Keyboard_IsPress(DIK_SPACE) && cnt2 % 90 == 0)
		{
			Bullet_Create(Character.x, Character.y + 2.0f, Character.z+1.0f);
		}
		cnt2++;*/
		
	}

	//Player.HP = Get_Hp();
	
/*
	if (Flag)
	{
		Character = Keep_Character;
		Flag = false;
	}
*/	
/*	for (int i = 0; i < WALL_MAX; i++)
	{
		if (Get_Hit_Frag(i))
		{

			if (Character.z > Get_Wall(i).z)
			{
				Character.z = Keep_Character.z;

			}

			if (Character.z < Get_Wall(i).z)
			{
				Character.z = Keep_Character.z;


			}

			if (Character.z > Get_Wall(i).x || Character.z < Get_Wall(i).x)
			{
				Character.x = Keep_Character.x;
			}
			break;
		}
		
		break;
	}*/

	

	if (Case == 1)
	{
		CharaAng += 0.0f;
	}


	if (Character.x >FIELD_X/2)
	{
		Character.x = FIELD_X/2;
	}
	
	if (Character.x < -FIELD_X/2)
	{
		Character.x = -FIELD_X/2;
	}

	if (Character.z > FIELD_Z/2.8)
	{
		Character.z = FIELD_Z/2.8;
	}

	if (Character.z < -FIELD_Z/2)
	{
		Character.z = -FIELD_Z/2;
	}

	

	//座標確定
	Player.Collision.CenterPosition = Character;
	
	Player.Collision.radius = HIT_RADIUS;

	Shadow_Create(&Player.Collision.CenterPosition.x, &Player.Collision.CenterPosition.z, 2.4f, 2.4f, &Player.shadow_number);

	
}

void Character_Stop(void)
{
	if (Flag)
	{
		Character = Keep_Character;
	}

	else
	{
		Keep_Character = Character;
	}
}

void Character_Create(float x, float y, float z)
{
	if (!Player.flag)
	{
		Player.flag = true;
		Character = D3DXVECTOR3(x, y, z);
	}
}

void Character_Destroy(void)
{
	Player.flag = false;
}

void Character_Body_Draw(void)
{
	Character_Stop();

	if (Player.flag)
	{
		//もでる
		D3DXMATRIX mtxWorldModel;
		D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
		D3DXMATRIX mtxTranslationModel;
		D3DXMatrixTranslation(&mtxTranslationModel, Character.x, Character.y, Character.z);
		D3DXMATRIX mtxScaringModel;
		D3DXMatrixScaling(&mtxScaringModel, 0.2f, 0.2f, 0.2f);
		D3DXMATRIX mtxRotationModel;
		D3DXMatrixRotationY(&mtxRotationModel, D3DXToRadian(CharaAng));
		D3DXMATRIX mtxRotationModel2;
		D3DXMatrixRotationY(&mtxRotationModel2, D3DXToRadian(180));

		mtxWorldModel = mtxScaringModel* mtxRotationModel2*mtxRotationModel*mtxTranslationModel;

		Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
		Model_Draw(INDEX_MODEL_CHARA_BODY);

		g_Save_MatrixCharacter = mtxWorldModel;

		Character_Head();
		Character_Hand();
		Character_Leg();
	}
}

void Character_Head(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る
	
	/*D3DXMATRIX mtxScaringModel;
	D3DXMatrixScaling(&mtxScaringModel, 0.5f, 0.5f, 0.5f);
	mtxWorldModel = mtxScaringModel;*/
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixCharacter);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_CHARA_HEAD);
}

void Character_Hand(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る		
	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel,3.0f ,11.0f ,0.0f );
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationX(&mtxRotationModel, D3DXToRadian(Chara_Ang));

	mtxWorldModel = mtxRotationModel*mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixCharacter);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_CHARA_HAND);

	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る		
	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, -3.0f, 11.0f, 0.0f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(-Chara_Ang));
	mtxWorldModel2 =mtxRotationModel2* mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixCharacter);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_CHARA_HAND);
}

void Character_Leg(void)
{
	//もでる
	D3DXMATRIX mtxWorldModel;
	D3DXMatrixIdentity(&mtxWorldModel);//単位行列を作る		
	D3DXMATRIX mtxTranslationModel;
	D3DXMatrixTranslation(&mtxTranslationModel, 1.0f, 5.0f, 0.0f);
	D3DXMATRIX mtxRotationModel;
	D3DXMatrixRotationX(&mtxRotationModel, D3DXToRadian(Chara_Ang));
	mtxWorldModel =mtxRotationModel* mtxTranslationModel;
	D3DXMatrixMultiply(&mtxWorldModel, &mtxWorldModel, &g_Save_MatrixCharacter);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel);//ワールド変換行列
	Model_Draw(INDEX_MODEL_CHARA_LEG);

	//もでる
	D3DXMATRIX mtxWorldModel2;
	D3DXMatrixIdentity(&mtxWorldModel2);//単位行列を作る		
	D3DXMATRIX mtxTranslationModel2;
	D3DXMatrixTranslation(&mtxTranslationModel2, -1.0f, 5.0f, 0.0f);
	D3DXMATRIX mtxRotationModel2;
	D3DXMatrixRotationX(&mtxRotationModel2, D3DXToRadian(-Chara_Ang));
	mtxWorldModel2 =mtxRotationModel2* mtxTranslationModel2;
	D3DXMatrixMultiply(&mtxWorldModel2, &mtxWorldModel2, &g_Save_MatrixCharacter);
	Direct3D_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorldModel2);//ワールド変換行列
	Model_Draw(INDEX_MODEL_CHARA_LEG);
}



D3DXVECTOR3 Get_Chara_Pos(void)
{
	return Character;
}

D3DXVECTOR3 Get_Chara_Front(void)
{
	return Front;
}

D3DXVECTOR3 Get_Chara_Right(void)
{
	return Right;
}
D3DXVECTOR3 Get_Chara_Up(void)
{
	return Up;
}

float Get_Ang(void)
{
	return CharaAng;
}

const SphereCollision* Chara_GetCollision(void)
{
	return &Player.Collision;
}

void Wall_Hit_Frag(bool flag)
{
	Flag = flag;
}

bool Get_Hit_Frag(void)
{
	return Flag;
}

PLAYER Get_Player(void)
{
	return Player;
}
