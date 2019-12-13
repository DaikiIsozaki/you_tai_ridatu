#include<Windows.h>
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"common.h"
#include"direct3d.h"
#include"texture.h"
#include"sprite.h"

//�O���[�o���ϐ�
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;	//�f�o�C�X�̃C���^�[�t�F�C�X
static LPDIRECT3DTEXTURE9 g_pTexture = NULL;
static LPDIRECT3D9 g_pD3D = NULL;

//���C��

//Direct3D�̏�����
bool Direct3D_Initialize(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D==NULL)
	{
		return false;
	}

	D3DPRESENT_PARAMETERS d3dpp = {};
	//LPDIRECT3DDEVICE9 g_pD3DDevice;

	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = true;		//�t���X�N���[�����[�h�Ȃ�false,�E�B���h�E���[�h�Ȃ�true
	d3dpp.EnableAutoDepthStencil = true;	//DepthStencil��on/off
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;	//�[���o�b�t�@��16�r�b�g�p�ӂ���
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//�t���X�N���[������Ȃ��ƈӖ��Ȃ�
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pD3DDevice);
/*
	if (FAILED(D3DXCreateTextureFromFile(g_pD3DDevice, "witch3.png", &g_pTexture)))

	{
		//���s������
		MessageBox(hWnd, "�łˁ`�`�`", "�m�F", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK;
	}
	*/
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(0,0,0,255));
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(100, 0, 0, 255));



	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	//�A���t�@�u�����h��L���ɂ���
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	//�w�i(���łɕ`���ꂽ���)DEST �̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//������`���|���S��SRC(�\�[�X)�̃u�����h�ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	

	return true;
}

//Direc3D�I������
void Direct3D_Finalize(void)
{
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
}

//Direct3D�f�o�C�X�|�C���^�̎擾
LPDIRECT3DDEVICE9 Direct3D_GetDevice(void)
{
	return g_pD3DDevice;
}