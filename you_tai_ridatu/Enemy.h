#ifndef ENEMY_H
#define ENEMY_H

#include"SphereCollision.h"


#define ENEMY_MAX	(1)

void Enemy_Init(void);
void Enemy_Uninit(void);
void Enemy_Update(int Case);
void Enemy_Stop(int index);
void Enemy_Draw(void);
void Enemy_body_Draw(void);
void Enemy_head_Draw(int index);
void Enemy_hand_Draw(int index);
void Enemy_leg_Draw(int index);
void Enemy_Create(float x,float y,float z,int type,float Ang);
void Enemy_Destroy(int index);
bool Enemy_IsEnable(int index);
const SphereCollision* Enemy_GetCollision(int index);
D3DXVECTOR3 Enemy_GetPos(int index);
void Wall_Hit_Enemy(int index, bool flag);

enum
{
	ENEMY_TYPE_0,
	ENEMY_TYPE_TEST,
	Enemy_TYPE_COA,
	
};

#endif // !ENEMY_H
#pragma once
