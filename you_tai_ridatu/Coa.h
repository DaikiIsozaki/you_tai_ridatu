#ifndef COA_H
#define COA_H

#include"SphereCollision.h"

#define COA_MAX	(1)

void Coa_Init(void);
void Coa_Uninit(void);
void Coa_Update(int Case);
void Coa_Draw(void);
void Coa_Create(float x, float y, float z);
void Coa_Destroy(int index);
bool Coa_IsEnable(int index);
const SphereCollision* Coa_GetCollision(int index);

#endif // !COA_H
#pragma once
