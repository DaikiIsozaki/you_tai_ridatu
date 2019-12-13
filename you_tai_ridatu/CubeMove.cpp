#include"Cube.h"
#include<d3dx9.h>
#include"direct3d.h"
#include"common.h" 

typedef struct
{
	float x;//xÀ•W
	float z;//yÀ•W
	float Xs;//xŠg‘å
	float Ys;//yŠg‘å
	float Zs;//zŠg‘å
	bool Xm=true;
	bool Zm=false;
}CUBE;

CUBE Cube;
void CubeMove_Init(void)
{
	Cube.x = 0.0f;
	Cube.z = 0.0f;

}

void CubeMove_Uninit(void)
{

}

void CubeMove_Update(void)
{
	if (Cube.Xm && !Cube.Zm)
	{
		Cube.x += 0.01f;
		
		if (Cube.x >= 9.0f)
		{
			Cube.Xm = false;
			Cube.Zm = true;
		}
		
	}
	if (!Cube.Xm&&Cube.Zm)
	{
		Cube.z -= 0.01f;
		if (Cube.z <= -9.0f)
		{
			Cube.Zm = false;
		}
	}
	if (!Cube.Xm && !Cube.Zm)
	{
		Cube.x -= 0.01f;
		if (Cube.x <= 0.0f)
		{
			Cube.Xm = true;
			Cube.Zm = true;
		}
	}
	if (Cube.Xm&&Cube.Zm)
	{
		Cube.z += 0.01f;
		if (Cube.z >= 0.0f)
		{
			Cube.Zm = false;
		}
	}	
}

void CubeMove_Draw(void)
{

}

float CubeX(void)
{
	return Cube.x;
}

float CubeZ(void)
{
	return Cube.z;
}

