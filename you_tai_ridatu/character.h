#ifndef CHARACTER_H
#define CHARACTER_H

#include"SphereCollision.h"

#define PLAYER_HP		(30)

typedef struct Player_tag
{
	SphereCollision Collision;
	int a;
	int HP;
	int shadow_number;
	bool flag;
}PLAYER;

void Character_Init(void);
void Character_Uninit(void);
void Character_Update(int Case);
void Character_Body_Draw();
void Character_Create(float x, float y, float z);
void Character_Destroy(void);
void Character_Head(void);
void Character_Hand(void);
void Character_Leg(void);
void Character_Stop(void);
D3DXVECTOR3 Get_Chara_Pos(void);
D3DXVECTOR3 Get_Chara_Front(void);
D3DXVECTOR3 Get_Chara_Right(void);
D3DXVECTOR3 Get_Chara_Up(void);
float Get_Ang(void);
const SphereCollision* Chara_GetCollision(void);
void Wall_Hit_Frag(bool flag);
bool Get_Hit_Frag(void);
PLAYER Get_Player(void);


#endif // !CHARACTER_H
#pragma once
