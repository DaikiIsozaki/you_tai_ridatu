#ifndef EXP_H_
#define EXP_H_

void Exp_Init(void);
void Exp_Update(void);

void Exp_Draw(void);
void Exp_Create(float Ex, float Ey, float Ez);
void Effect_Destroy(int i);
bool Effect_IsEnable(int i);


#endif  //EXP_H_