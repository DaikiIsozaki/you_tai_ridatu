#ifndef WALL_H
#define WALL_H

#include"SphereCollision.h"


#define WALL_MAX	(147)

typedef struct Wall_Pos_tag
{
	float x, y, z;
}WALL_POS;

void Wall_Init(void);
void Wall_Uninit(void);
void Wall_Update(void);
void Wall_Draw(void);
void Wall_Create(float x,float y,float z,int type);
bool Wall_IsEnable(int index);
void Wall_Hit_Frag(int index, bool type);
bool Get_Hit_Frag(int index);
const SphereCollision* Wall_GetCollision(int index);
D3DXVECTOR3 Get_Wall(int index);
WALL_POS Get_Wall_Pos(int index);
D3DXVECTOR3 Get_Wall_Center_Pos(int index);
void Wall_Hit(int index, bool Hit_Flag);

enum
{
	WALL_TYPE_0,
	WALL_TYPE_1,//ê≥ñ ÅAîwñ 
	WALL_TYPE_2,//ç∂âEñ 
	WALL_TYPE_3,//è„â∫ñ 

	WALL_TYPE_MAX,


};

#endif // !WALL_H
#pragma once
