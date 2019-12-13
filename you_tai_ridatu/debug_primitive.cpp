#include<d3dx9.h>
#include"direct3d.h"
#include<math.h>

#define CIRCLE_VERTEX_COUNT	(8)
#define CIRCLE_DRAW_MAX		(2048)
#define FVF_DEBUG_VERTEX	(D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

typedef struct DebugVertex_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
}DebugVertex;

static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;

static int g_CircleCount = 0;
static DebugVertex* g_pDebugVertex=NULL;
static WORD* g_pDebugVertexIndex=NULL;



void DebugPrimitive_Initialize(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	pDevice->CreateVertexBuffer(sizeof(DebugVertex)*CIRCLE_VERTEX_COUNT*CIRCLE_DRAW_MAX,D3DUSAGE_WRITEONLY,FVF_DEBUG_VERTEX,D3DPOOL_MANAGED,&g_pVertexBuffer,NULL);

	pDevice->CreateIndexBuffer(sizeof(WORD)*CIRCLE_VERTEX_COUNT*2*CIRCLE_DRAW_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16,D3DPOOL_MANAGED,&g_pIndexBuffer,NULL);
	
	g_CircleCount = 0;


}
void Debug_Primitive_Finalize(void)
{
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer -> Release();
		g_pIndexBuffer = NULL;
	}
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

void Debug_Primitive_BatchBegin(void)
{
	g_CircleCount = 0;

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pDebugVertex,0 );

	g_pIndexBuffer->Lock(0, 0, (void**)&g_pDebugVertexIndex,0 );
}
void Debug_Primitive_BatchDrawCircle(float x, float y,float radius)
{
	int n = g_CircleCount*CIRCLE_VERTEX_COUNT;

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;

	for (int i = 0;i < CIRCLE_VERTEX_COUNT;i++)
	{
		g_pDebugVertex[n + i].position.x = cos(i*s)*radius + x;
		g_pDebugVertex[n + i].position.y = sin(i*s)*radius + y;
		g_pDebugVertex[n + i].position.z = 1.0f;
		//g_pDebugVertex[n + i].position.w = 1.0f;
		g_pDebugVertex[n + i].color = D3DCOLOR_RGBA(0,255,0,255);

		g_pDebugVertexIndex[n * 2 + i * 2] = n + i;
		g_pDebugVertexIndex[n * 2 + i * 2 + 1] = n + (i + 1) % CIRCLE_VERTEX_COUNT;
	}
	g_CircleCount++;

	
}
void Debug_Primitive_BatchRun(void)
{
	LPDIRECT3DDEVICE9 pDevice = Direct3D_GetDevice();

	g_pVertexBuffer->Unlock();
	g_pIndexBuffer->Unlock();

	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(DebugVertex));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetFVF(FVF_DEBUG_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0,0,CIRCLE_VERTEX_COUNT*CIRCLE_DRAW_MAX,0,g_CircleCount*CIRCLE_VERTEX_COUNT);

	

}