//=====================================================
//
//	Direct3D�̏�����
//
//	Author : ����P	
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
//�萔��`
/////////////////////////////////////////////////////////
#define CLASS_NAME		"GameWindow"
#define WINDOW_CAPTION	"YOU-��_���E"

#define Window_width	(1500)
#define Window_height	(1000)






/////////////////////////////////////////////////////////
//�v���g�^�C�v�錾
/////////////////////////////////////////////////////////
static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;



//�Q�[���̏������֐�
static bool Initialize(HINSTANCE hInstance, HWND hWnd);
//�X�V
static void Update(HWND hWnd);
//�`��
static void Draw(void);
//�I��
static void Finalize(void);

//////////////////////////////////////////////////////////
//�O���[�o���ϐ�
//////////////////////////////////////////////////////////
static int g_FrameCount = 0;
static int g_BaseFrame = 0;
static double g_BaseTime = 0;
static double g_FPS = 0.0f;
static double g_ReserveTime = 0.0f;


/////////////////////////////////////////////////////////
//���C��
/////////////////////////////////////////////////////////
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };//{0,0,��,����}
	AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME), FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	WNDCLASS wc = {};//WindowClass�̍쐬	wc...WindowClass	wc={};...wc��������
	wc.lpfnWndProc = WndProc;//�E�B���h�E�v���V�[�W��
	wc.lpszClassName = CLASS_NAME;//�N���X��
	wc.hInstance = hInstance;//�C���X�^���X�n���h��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);//�}�E�X�J�[�\��
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);//�w�i�F

	RegisterClass(&wc);//�V�X�e���̓o�^

	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	int window_x = (desktop_width - Window_width) / 2;
	int window_y = (desktop_height - Window_height) / 2;

	

	HWND hWnd = CreateWindow(
		CLASS_NAME,//�E�B���h�E�N���X��									
		WINDOW_CAPTION,//�L���v�V����										  
		WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX | WS_THICKFRAME),//�E�B���h�E�X�^�C���t���O(�r�b�g)	�ő剻���ł��Ȃ�	
		//CW_USEDEFAULT,//�E�B���h�E���Wx										  
		//CW_USEDEFAULT,//�E�B���h�E���Wy														------>�E�B���h�E�n���h��
		window_x,
		window_y,
		Window_width,
		Window_height,

		//CW_USEDEFAULT,//�E�B���h�E�̕�													�����s�����hWnd��0������
		//CW_USEDEFAULT,//�E�B���h�E�̍���
		NULL,//�e�E�B���h�E�n���h��
		NULL,//���j���[
		hInstance,//�C���X�^���X�n���h��
		NULL//�E�B���h�E���b�Z�[�W�ő����I���W�i���f�[�^�Ȃǂ̃|�C���^
	);

	
	ShowWindow(hWnd, nCmdShow);//��1�����̃E�B���h�E���2�����̏�Ԃŏo��
	UpdateWindow(hWnd);
	

	//�Q�[���̏������iDirect3D�̏������j
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

			//�Q�[���̍X�V
			Update(hWnd);
			//�Q�[���̕`��
			Draw();

		}
	} while (msg.message != WM_QUIT);

	//�Q�[���̏I������
	Finalize();

	return(int)msg.wParam;


}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//�E�B���h�E�v���V�[�W��
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
		if (MessageBox(hWnd, "�{���ɏI�����Ă�낵���ł����H", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK)
		{
			DestroyWindow(hWnd);//YES�Ȃ�
		}

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);//���ꂳ������Ί�{�I�Ȃ��Ƃ͂���Ă����
}
//�Q�[���̏������֐�
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
//�X�V
void Update(HWND hWnd)
{

	scene_Update();
	fade_Update();
	Keyboard_Update();
	//Game_Update();
	
}
//�`��
void Draw(void)
{

	LPDIRECT3DDEVICE9 Direct3D_GetDevice();

	if (!Direct3D_GetDevice())
	{
		return;
	}

	Direct3D_GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0 ,255, 255), 1.0f/*0����Ԏ�O�A1����ԉ�*/, 0);
	Direct3D_GetDevice()->BeginScene();

	//Game_Draw();

	scene_Draw();

	fade_Draw();
	
	Direct3D_GetDevice()->EndScene();

	Direct3D_GetDevice()->Present(NULL, NULL, NULL, NULL);

	//�V�[���`�F�b�N
	scene_Check();


}
//�I��
void Finalize(void)
{
	//�Q�[���̏I������
	//Game_Finalize();

	Direct3D_Finalize();

	Keyboard_Finalize();

	scene_Finalize();

	fade_Finalize();

	UninitSound();
}