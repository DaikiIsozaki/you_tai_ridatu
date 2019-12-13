#ifndef MESHFIELD_H
#define MESHFIELD_H

void MeshField_Init(float grid_W, int grid_tate, int grid_yoko);//1グリッドの幅,高さ　グリッド数
void MeshCylinder_Init(float meshH, float radius, int meshXnum, int meshYnum);//1メッシュの高さ、半径、1周に何面、壁の高さ
void MeshSkydome_Init(float meshH, float radius, int meshXnum, int meshYnum);
void MeshField_Uninit(void);
void MeshField_Draw(int index);


#endif // !MESHFIELD_H

