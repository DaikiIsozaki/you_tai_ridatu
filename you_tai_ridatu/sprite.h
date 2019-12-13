#ifndef SPRITE_H_
#define SPRITE_H_

#include<d3dx9.h>

void Sprite_Initialize(void);
void Sprite_Finalize(void);
void SetColor(D3DCOLOR color);
void Sprite_Draw(int texture_index, float dx, float dy, float rate);
void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate);

void Sprite_Draw_exp(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate, float Xx, float Yy);
void Sprite_Draw_exp2(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rate, int Xx, int Yy);


void Sprite_Draw(int texture_index, float dx, float dy, float tx, float ty, float tw, float th, float rotation);

#endif // !SPRITE_H_
