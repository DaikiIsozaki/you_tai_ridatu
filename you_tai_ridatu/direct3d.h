#ifndef DIRECT3D_H
#define DIRECT3D_H

#include<Windows.h>
#include<d3dx9.h>
#include<d3dx9.h>

//Direct3D�̏�����
//
//�߂�l�F���s������false
//
//�����F�E�E�E�E�B���h�E�n���h��
//
bool Direct3D_Initialize(HWND hWnd);	


//Direc3D�I������
void Direct3D_Finalize(void);

//Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 Direct3D_GetDevice(void);




#endif // !DIRECT3D_H
