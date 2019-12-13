//=====================================================
//
//	Direct3Dの初期化
//
//	Author : 磯崎大輝	
//=====================================================

#define CRT_SECURE_NO_WARNINGS

#include<Windows.h>
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"sprite.h"
#include"game.h"
#include"input.h"
#include"Cube.h"
#include"debug.h"
#include"system_timer.h"
#include<stdio.h>
#include"debug_primitive.h"
#include"grid.h"
#include"fade.h"
#include"scene.h"
#include"sound.h"




/////////////////////////////////////////////////////////
//定数定義
/////////////////////////////////////////////////////////
#define CLASS_NAME		"GameWindow"
#define WINDOW_CAPTION	"YOU-体_離脱"

#define Window_width	(1500)
#define Window_height	(1000)






/////////////////////////////////////////////////////////
//プロトタイプ宣言
/////////////////////////////////////////////////////////
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;



//ゲームの初期化関数
static bool Initialize(HINSTANCE hInstance, HWND hWnd);
//更新
static void Update(HWND hWnd);
//描画
static void Draw(void);
//終了
static void Finalize(void);

//////////////////////////////////////////////////////////
//グローバル変数
//////////////////////////////////////////////////////////
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0f;
static double g_ReserveTime = 0.0f;


/////////////////////////////////////////////////////////
//メイン
/////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//{0,0,幅,高さ}
	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	WNDCLASS wc = {};//WindowClassの作成	wc...WindowClass	wc={};...wcを初期化
	wc.lpfnWndProc = WndProc;//ウィンドウプロシージャ
	wc.lpszClassName = CLASS_NAME;//クラス名
	wc.hInstance = hInstance;//インスタンスハンドル
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//マウスカーソル
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);//背景色

	RegisterClass(&wc);//システムの登録

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_x = (desktop_width - Window_width) / 2;
	int window_y = (desktop_height - Window_height) / 2;

	

	HWND hWnd = CreateWindow(
		CLASS_NAME,//ウィンドウクラス名									
		WINDOW_CAPTION,//キャプション										  
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),//ウィンドウスタイルフラグ(ビット)	最大化ができない	
		//CW_USEDEFAULT,//ウィンドウ座標x										  
		//CW_USEDEFAULT,//ウィンドウ座標y														------>ウィンドウハンドル
		window_x,
		window_y,
		Window_width,
		Window_height,

		//CW_USEDEFAULT,//ウィンドウの幅													※失敗するとhWndに0が入る
		//CW_USEDEFAULT,//ウィンドウの高さ
		NULL,//親ウィンドウハンドル
		NULL,//メニュー
		hInstance,//インスタンスハンドル
		NULL//ウィンドウメッセージで送れるオリジナルデータなどのポインタ
	);

	
	ShowWindow(hWnd, nCmdShow);//第1引数のウィンドウを第2引数の状態で出す
	UpdateWindow(hWnd);
	

	//ゲームの初期化（Direct3Dの初期化）
	Initialize(hInstance, hWnd);

	MSG msg = {};
	do
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			double time = SystemTimer_GetTime();
			if ((time - g_ReserveTime) <= 1.0f / 60.0f)
			{
				continue;
			}
			g_ReserveTime = time;

			//ゲームの更新
			Update(hWnd);
			//ゲームの描画
			Draw();

		}
	} while (msg.message != WM_QUIT);

	//ゲームの終了処理
	Finalize();

	return(int)msg.wParam;


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//ウィンドウプロシージャ
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいですか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);//YESなら
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//これさえあれば基本的なことはやってくれる
}
//ゲームの初期化関数
bool Initialize(HINSTANCE hInstance, HWND hWnd)
{
	
	if (!Keyboard_Initialize(hInstance, hWnd))
	{
		return false;
	}
	if (!Direct3D_Initialize(hWnd))
	{
		return false;
	}

	Texture_Load();
	//Game_Initialize();

	InitSound(hWnd);

	scene_Initialize(SCENE_INDEX_TITLE);
	fade_Initialize();
	
	g_ReserveTime=g_BaseTime = SystemTimer_GetTime();
	g_FrameCount = g_BaseFrame = 0;


	return true;
}
//更新
void Update(HWND hWnd)
{

	scene_Update();
	fade_Update();
	Keyboard_Update();
	//Game_Update();
	
}
//描画
void Draw(void)
{

	LPDIRECT3DDEVICE9 Direct3D_GetDevice();

	if (!Direct3D_GetDevice())
	{
		return;
	}

	Direct3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0 ,255, 255), 1.0f/*0が一番手前、1が一番奥*/, 0);
	Direct3D_GetDevice()->BeginScene();

	//Game_Draw();

	scene_Draw();

	fade_Draw();
	
	Direct3D_GetDevice()->EndScene();

	Direct3D_GetDevice()->Present(NULL, NULL, NULL, NULL);

	//シーンチェック
	scene_Check();


}
//終了
void Finalize(void)
{
	//ゲームの終了処理
	//Game_Finalize();

	Direct3D_Finalize();

	Keyboard_Finalize();

	scene_Finalize();

	fade_Finalize();

	UninitSound();
}