#ifndef CAMERA_H
#define CAMERA_H

void Camera_Init(void);
void Camera_Update(int Case);

D3DXVECTOR3 Get_Cube(void);
D3DXMATRIX Get_View(void);
D3DXVECTOR3 Get_Heri(void);
D3DXVECTOR3 Get_Front(void);
D3DXVECTOR3 Get_Right(void);
D3DXVECTOR3 Get_Up(void);

#endif // !CAMERA_H
#pragma once
