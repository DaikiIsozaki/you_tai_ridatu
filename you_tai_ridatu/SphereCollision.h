#ifndef SPHERECOLLISION_H
#define SPHERECOLLISION_H
#include<d3dx9.h>

typedef struct SphereCollision_tag
{
	D3DXVECTOR3 CenterPosition;
	float radius;

}SphereCollision;

bool HitSphereCollision(const SphereCollision* pA, const SphereCollision* pB);
void AtariHantei_Enemy(void);
void AtariHantei_Wall(void);
void AtariHantei_Gost(int Case);
void Scene_Change(void);
int Get_Enemy_Num(void);
int Get_Coa_Num(void);


#endif // !SPHERECOLLISION_H
#pragma once
