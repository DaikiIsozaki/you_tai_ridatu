#include "bullet.h"
#include <d3dx9.h>
#include "common.h"
#include "input.h"
#include "model.h"
#include"direct3d.h"
#include "camera.h"
#include "BillBoard.h"
#include "exp.h"
#include"character.h"
#include"Enemy.h"

#define TAMA_SPEED	(0.1f)
#define TAMA_RADIUS	(3.0f)
//#define BULLET_SIZE_X (30.0f)
//#define BULLET_SIZE_Y (30.0f)
//#define BULLET_SIZE_Y (30.0f)


int i;
static bool bBulletEnable = false;
//static  Circle g_BulletCollision = { 0 };


typedef struct {
	D3DXVECTOR3 Bullet_position;
	bool  Bullet_Flg;
	SphereCollision Collision;
}BULLET;



BULLET g_Bullet[BULLET_MAX];


D3DXMATRIX Bullet_World[BULLET_MAX];
D3DXMATRIX Bullet_Rcation[BULLET_MAX];
D3DXMATRIX Bullet_Trans[BULLET_MAX];
D3DXMATRIX Bullet_Scale[BULLET_MAX];

D3DXVECTOR3 Bullet_position_stock[BULLET_MAX];

int Exp_flg[BULLET_MAX];


void Bullet_Init(void)
{
	//�e�̃��f�����[�h
	Model_Xfile_Load(INDEX_MODEL_KING);

	//�O���[�o���ϐ���������
	for (i = 0; i < BULLET_MAX; i++)
	{
		g_Bullet[i].Bullet_position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		g_Bullet[i].Bullet_Flg = false;
		
		Exp_flg[i] = 0;
		//g_Bullet[i].btCollision.cx = g_Bullet[i].btX;
		//g_Bullet[i].btCollision.cy = g_Bullet[i].btY;
	}


}



void Bullet_Uninit(void)
{
	Model_Finalise(INDEX_MODEL_KING);
}



void Bullet_Update(void)
{

	//�e���L���Ȃ�
	//�@�e���W�X�V
	
	for (i = 0; i < BULLET_MAX; i++)
	{

		g_Bullet[i].Bullet_position += Bullet_position_stock[i] * TAMA_SPEED;

		
		//��
		if (g_Bullet[i].Bullet_position.z > FIELD_Z)//100.0f�͕ǂ̍��W�Ȃ�Ŏ����ŕς��Ă�
		{
			//Exp_Create(g_Bullet[i].Bullet_position.x, g_Bullet[i].Bullet_position.y + 1.0f, g_Bullet[i].Bullet_position.z - 6.0f);
			g_Bullet[i].Bullet_Flg = false;
		}
		//��O
		if (g_Bullet[i].Bullet_position.z < -FIELD_Z)
		{
			//Exp_Create(g_Bullet[i].Bullet_position.x, g_Bullet[i].Bullet_position.y + 1.0f, g_Bullet[i].Bullet_position.z + 6.0f);
			g_Bullet[i].Bullet_Flg = false;
		}
		//�E
		if (g_Bullet[i].Bullet_position.x > FIELD_X)
		{
			//Exp_Create(g_Bullet[i].Bullet_position.x - 6.0f, g_Bullet[i].Bullet_position.y + 1.0f, g_Bullet[i].Bullet_position.z);
			g_Bullet[i].Bullet_Flg = false;

		}
		//��
		if (g_Bullet[i].Bullet_position.x < -FIELD_X)
		{
			//Exp_Create(g_Bullet[i].Bullet_position.x + 6.0f, g_Bullet[i].Bullet_position.y + 1.0f, g_Bullet[i].Bullet_position.z + 6.0f);
			g_Bullet[i].Bullet_Flg = false;

		}

		g_Bullet[i].Collision.CenterPosition = g_Bullet[i].Bullet_position;
		g_Bullet[i].Collision.radius = TAMA_RADIUS;

		/*if (g_Bullet[i].Bullet_Flg == true)
		{

			//g_Bullet[i].Bullet_position.y = 0.0f;
			

			//g_Bullet[i].btCollision.cx = g_Bullet[i].btX;
			//g_Bullet[i].btCollision.cy = g_Bullet[i].btY;

		//�A�e����ʊO�ɏo����e�𖳌��ɂ���
			

			

		}*/
		
		

	}

}

void Bullet_Create(float x, float y, float z)
{
	//�e���L���Ȃ�c�@�����߂��H
	for (i=0; i<BULLET_MAX; i++)
	{
		if (g_Bullet[i].Bullet_Flg == false)
		{
	
			//�e�̐����|�W�V����
			g_Bullet[i].Bullet_position.x = x;
			g_Bullet[i].Bullet_position.y = y;
			g_Bullet[i].Bullet_position.z = z;
			Bullet_position_stock[i] = Get_Chara_Front();
			g_Bullet[i].Bullet_Flg = true;
			break;
		}
		
	}

	//�e�̍��W��x,y�ɂ���
	//�e��L����
}



void Bullet_Draw(void)
{
	LPDIRECT3DDEVICE9 pD3DDevice = Direct3D_GetDevice();
	//�e���L����������e�\��
	for (i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullet[i].Bullet_Flg == true)
		{
			D3DXMatrixIdentity(&Bullet_World[i]);

			D3DXMatrixRotationY(&Bullet_Rcation[i], D3DXToRadian(-90));

			//�g��
			D3DXMatrixScaling(&Bullet_Scale[i], 0.0f, 0.0f, 0.0f);

			D3DXMatrixTranslation(&Bullet_Trans[i], g_Bullet[i].Bullet_position.x, g_Bullet[i].Bullet_position.y, g_Bullet[i].Bullet_position.z);

			//����
			//D3DXMatrixMultiply(&Bullet_World[i], &Bullet_Rcation[i], &Bullet_Scale[i]);
			//D3DXMatrixMultiply(&Bullet_World[i], &Bullet_World[i], &Bullet_Trans[i]);

			Bullet_World[i] = Bullet_Scale[i] * Bullet_Rcation[i] *  Bullet_Trans[i];

			pD3DDevice->SetTransform(D3DTS_WORLD, &Bullet_World[i]);
			//BB_Exp_Draw2(g_Bullet[i].Bullet_position.x, g_Bullet[i].Bullet_position.y, g_Bullet[i].Bullet_position.z );
		}
	}
	

}

void Bullet_Destroy(int index)
{
	//�e�𖳌��ɂ���
	g_Bullet[index].Bullet_Flg = false;
}



bool Bullet_IsEnable(int i)
{
	return g_Bullet[i].Bullet_Flg;
}


D3DXVECTOR3 Get_Bullet(int i)
{
	return g_Bullet[i].Bullet_position;
}

const SphereCollision* Bullet_GetCollision(int index)
{
	return &g_Bullet[i].Collision;
}

/*Circle* Bullet_GetCollision(int i)
{
	return &g_Bullet[i].btCollision;
}*/
