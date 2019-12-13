#ifndef SCORE_H
#define SCORE_H

void Score_Initialize(int digit);
void Score_Finalize(void);
void Score_Draw(float x, float y, int score, bool bZero, bool bLeft);	//Å‰‚ÌˆêŒ…‚Ì”ñ•\¦Draw
void Score_Draw2(float x, float y, int score, bool bZero, bool bLeft);
void Score_Draw3(float x, float y, int score, int fig, bool bLeft, bool bZero);


#endif // !SCORE_H
