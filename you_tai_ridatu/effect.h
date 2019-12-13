#ifndef EFFECT_H
#define EFFECT_H


#include<d3d9.h>

//”š”­

void Effect_Initialize(void);
void Effect_Finalize(void);
void Effect_Update(void);
void Effect_Create(float x, float y);
void Effect_Draw(void);
void Effect_Destroy(int index);

bool Effect_IsEnable(void);
//const Circle* Effect_GetCollision(void);

//

void Effect2_Initialize(void);
void Effect2_Finalize(void);
void Effect2_Update(void);
void Effect2_Draw(void);

void Effect2_Create(float x, float y,float radius,int life, D3DCOLOR color);

#endif // !EFFECT_H

