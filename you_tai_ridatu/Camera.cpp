#include"direct3d.h"
#include"common.h"
#include"input.h"
#include"soukousya.h"
#include"character.h"
#include"Dummy.h"
#include"wall.h"

#define CAMER_LENGTH	(8.0f)

D3DXVECTOR3 eye(0.0f, 0.0f, 0.0f);//�J�����ʒu
D3DXVECTOR3 at(Get_Chara_Pos().x, Get_Chara_Pos().y, Get_Chara_Pos().z);//���Ă�ʒu

D3DXVECTOR3 CPosition;//�J�������W 
D3DXVECTOR3 CPosition2;//�J�������W 
static float Length;//g_CameraPosition����at�܂ł̒���
float Length2;

typedef struct
{
	D3DXVECTOR3 CFront[2];//�J�����̌����x�N�g��(�P�ʃx�N�g��)���K������1
	D3DXVECTOR3 CRight[2];
	D3DXVECTOR3 CUp[2];
}CAMERA;

CAMERA Camera;


D3DXVECTOR3 CSpeed;

D3DXVECTOR3 CCube;


float Speed;

//�r���[�ϊ��s��̍쐬�Ɛݒ�
D3DXMATRIX mtxView;

void Camera_Init(void)
{
	CPosition = D3DXVECTOR3(Get_Dummy_Pos().x, Get_Dummy_Pos().y + 15.0f, Get_Dummy_Pos().z + 20.0f);
	CPosition2 = D3DXVECTOR3(Get_Dummy_Pos().x, Get_Dummy_Pos().y + 15.0f, Get_Dummy_Pos().z + 20.0f);
	Length = CAMER_LENGTH;
	Length2 = 0.0f;
	for (int i = 0; i < 2; i++)
	{
		Camera.CFront[i] = D3DXVECTOR3(0.0f, -0.5f, 1.0f);
		Camera.CUp[i] = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		D3DXVec3Cross(&Camera.CRight[i], &Camera.CFront[i], &Camera.CUp[i]);
		D3DXVec3Normalize(&Camera.CRight[i], &Camera.CRight[i]);
		D3DXVec3Cross(&Camera.CUp[i], &Camera.CRight[i], &Camera.CFront[i]);
		D3DXVec3Normalize(&Camera.CUp[i], &Camera.CUp[i]);
		D3DXVec3Normalize(&Camera.CFront[i], &Camera.CFront[i]);
	}
	Speed = 0.01f;
	D3DXVECTOR3 CSpeed(0.0f, 0.0f, 0.0f);//�����p

	CCube = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	at = Get_Dummy_Pos();
}

/*
//����

	CPosition=Camera.CFront[i]*���x
				
	D3DXVECTOR3 speed(0.0f,0.0f,0.0f);
	�L�[����=>speed+=front*���x(�����x)
	
	speed*=0.98f;
*/



void Camera_Update(int Case)
{
	

	D3DXMATRIX mtxR;

	if (Case == 0 || Case == 2)
	{
		at = Get_Chara_Pos();
		CPosition2 = CPosition;
		/*Camera.CFront[1] = Camera.CFront[0];
		Camera.CRight[1] = Camera.CRight[0];
		Camera.CUp[1] = Camera.CUp[0];*/

		if (Keyboard_IsPress(DIK_1))
		{
			D3DXVECTOR3 f(Get_tank());
			f.y = 0.0f;
			CPosition.x += f.x*Speed;

			
			f.y = 0.0f;
			CPosition2.x += f.x*Speed;

		}
		if (Keyboard_IsPress(DIK_2))
		{
			D3DXVECTOR3 f(Get_tank());
			f.y = 0.0f;
			CPosition.x -= f.x*Speed;

			f.y = 0.0f;
			CPosition2.x -= f.x*Speed;
		}
		/*
		if (Keyboard_IsPress(DIK_A))
		{
		D3DXVECTOR3 f(Camera.CRight[i]);

		CPosition -= f*Speed;
		}
		if (Keyboard_IsPress(DIK_D))
		{
		D3DXVECTOR3 f(Camera.CRight[i]);

		CPosition += f*Speed;
		}

		if (Keyboard_IsPress(DIK_Q))
		{
		D3DXVECTOR3 f(CUp);

		CPosition += CUp*Speed;
		}

		if (Keyboard_IsPress(DIK_E))
		{
		D3DXVECTOR3 f(CUp);

		CPosition -= CUp*Speed;
		}
		*/
		//�����_��]
		if (Keyboard_IsPress(DIK_4))
		{

			D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);

			D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[1], &Camera.CFront[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[1], &Camera.CRight[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[1], &Camera.CUp[1], &mtxR);
		}

		if (Keyboard_IsPress(DIK_3))
		{

			D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);

			D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[1], &Camera.CFront[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[1], &Camera.CRight[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[1], &Camera.CUp[1], &mtxR);
		}

		
		//�����_��]�I��
		
		if (Keyboard_IsPress(DIK_LEFT))
		{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR,-0.002);
		D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);
		}

		if (Keyboard_IsPress(DIK_RIGHT))
		{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationY(&mtxR, 0.002f);
		D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);
		}

		if (Keyboard_IsPress(DIK_UP))
		{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR,&Camera.CRight[0], 0.002);
		D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);
		}

		if (Keyboard_IsPress(DIK_DOWN))
		{
		D3DXMATRIX mtxR;
		D3DXMatrixRotationAxis(&mtxR,&Camera.CRight[0], -0.002);
		D3DXVec3TransformNormal(&Camera.CFront[0], &Camera.CFront[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CRight[0], &Camera.CRight[0], &mtxR);
		D3DXVec3TransformNormal(&Camera.CUp[0], &Camera.CUp[0], &mtxR);
		}
		
		//�J�����|�W�V����
		CPosition = at - Camera.CFront[0]*Length;



		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//�J�����̏����
		D3DXMatrixLookAtLH(&mtxView, &CPosition, &at, &Camera.CUp[0]);

	}

	if (Case == 1)
	{
		at = Get_Dummy_Pos();

		if (Keyboard_IsPress(DIK_1))
		{
			D3DXVECTOR3 f(Get_tank());
			f.y = 0.0f;
			CPosition2.x += f.x*Speed;

		}
		if (Keyboard_IsPress(DIK_2))
		{
			D3DXVECTOR3 f(Get_tank());
			f.y = 0.0f;
			CPosition2.x -= f.x*Speed;
		}

		//�����_��]
		if (Keyboard_IsPress(DIK_4))
		{
			
			D3DXMatrixRotationY(&mtxR, D3DXToRadian(0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[1], &Camera.CFront[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[1], &Camera.CRight[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[1], &Camera.CUp[1], &mtxR);
		}

		if (Keyboard_IsPress(DIK_3))
		{
			D3DXMatrixRotationY(&mtxR, D3DXToRadian(-0.5f));
			D3DXVec3TransformNormal(&Camera.CFront[1], &Camera.CFront[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CRight[1], &Camera.CRight[1], &mtxR);
			D3DXVec3TransformNormal(&Camera.CUp[1], &Camera.CUp[1], &mtxR);
		}

		//�J�����|�W�V����
		CPosition2 = at - Camera.CFront[1]*Length;

		D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);//�J�����̏����
		D3DXMatrixLookAtLH(&mtxView, &CPosition2, &at, &Camera.CUp[1]);
		
	}
	

		Direct3D_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
		//�v���W�F�N�V�����ϊ��s��̍쐬�Ɛݒ�
		//�p�[�X�y�N�e�B�u
		D3DXMATRIX mtxProjection;
		D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)SCREEN_WIDTH / SCREEN_HEIGHT, 0.1f, 100.0f);
		Direct3D_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);
		Direct3D_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);
		Direct3D_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);

	
}
D3DXVECTOR3 Get_Cube(void)
{
	return CCube;
}
D3DXMATRIX Get_View(void)
{
	return mtxView;
}


D3DXVECTOR3 Get_Front(void)
{
	return Camera.CFront[0];
}
D3DXVECTOR3 Get_Right(void)
{
	return Camera.CRight[0];
}
D3DXVECTOR3 Get_Up(void)
{
	return Camera.CUp[0];
}

