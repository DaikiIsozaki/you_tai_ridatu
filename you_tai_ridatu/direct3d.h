#ifndef DIRECT3D_H
#define DIRECT3D_H

#include<Windows.h>
#include<d3dx9.h>
#include<d3dx9.h>

//Direct3Dの初期化
//
//戻り値：失敗したらfalse
//
//引数：・・・ウィンドウハンドル
//
bool Direct3D_Initialize(HWND hWnd);	


//Direc3D終了処理
void Direct3D_Finalize(void);

//Direct3Dデバイスポインタの取得
LPDIRECT3DDEVICE9 Direct3D_GetDevice(void);




#endif // !DIRECT3D_H
