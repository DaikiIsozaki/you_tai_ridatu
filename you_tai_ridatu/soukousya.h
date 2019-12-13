#ifndef SOUKOUSYA_H
#define SOUKOUSYA_H

void Soukousya_Init(void);
void Soukousya_Uninit(void);
void Soukousya_Updete(void);
void Soukousya_Draw(float x, float y, float z);
void Soukousya_Syashi_Draw(void);
void Soukousya_Taiya_Draw(void);
void Soukousya_Juza(void);
void Soukousya_Kiju(void);

void Soukousya1_body(float x, float y, float z);
void Soukousya1_houdai_dodai(void);
void Soukousya1_houdai(void);
void Soukousya1_kiju(void);
void Soukousya1_Left(void);
void Soukousya1_Right(void);

D3DXVECTOR3 Get_tank(void);
D3DXVECTOR3 Get_TankPos(void);

#endif // !SOUKOUSYA_H
#pragma once
