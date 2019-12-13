#ifndef BULLET_H_
#define BULLET_H_

//#include "judgement.h"
#include <d3dx9.h>
#include"SphereCollision.h"

#define BULLET_MAX (30)

void Bullet_Init(void);
void Bullet_Uninit(void);
void Bullet_Update(void);

void Bullet_Draw(void);
void Bullet_Create(float x, float y, float z);
void Bullet_Destroy(int index);

bool Bullet_IsEnable(int i);
D3DXVECTOR3 Get_Bullet(int i);
const SphereCollision* Bullet_GetCollision(int index);

//Circle* Bullet_GetCollision(int i);

#endif  //BULLET_H_