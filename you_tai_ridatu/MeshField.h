#ifndef MESHFIELD_H
#define MESHFIELD_H

void MeshField_Init(float grid_W, int grid_tate, int grid_yoko);//1�O���b�h�̕�,�����@�O���b�h��
void MeshCylinder_Init(float meshH, float radius, int meshXnum, int meshYnum);//1���b�V���̍����A���a�A1���ɉ��ʁA�ǂ̍���
void MeshSkydome_Init(float meshH, float radius, int meshXnum, int meshYnum);
void MeshField_Uninit(void);
void MeshField_Draw(int index);


#endif // !MESHFIELD_H

