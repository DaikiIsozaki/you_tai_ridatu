#ifndef DUMMY_H
#define DUMMY_H

#include"SphereCollision.h"

void Dummy_Init(void);
void Dummy_Uninit(void);
void Dummy_Update(int Case);
void Dummy_Draw(float x, float y, float z,int Case);
D3DXVECTOR3 Get_Dummy_Front(void);
D3DXVECTOR3 Get_Dummy_Right(void);
D3DXVECTOR3 Get_Dummy_Up(void);
D3DXVECTOR3 Get_Dummy_Pos(void);
float Get_Dummy_Ang(void);
const SphereCollision* Dummy_GetCollision(void);


#endif // !CHARACTER_H
#pragma once
#pragma once
