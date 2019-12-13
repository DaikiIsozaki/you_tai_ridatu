#ifndef FADE_H
#define FADE_H

#include<d3d9.h>

void fade_Initialize(void);
void fade_Finalize(void);
void fade_Update(void);
void fade_Draw(void);

void fade_Start(bool bOut, float frame, D3DCOLOR color);
bool Fade_IsFade(void);
float Fade_Alpha(void);


#endif // !FADE_H
