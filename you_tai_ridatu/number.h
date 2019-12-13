#ifndef NUMBER_H
#define NUMBER_H

void Number_Initialize(void);
void Number_Finalize(void);
// 0 <= n <= 9
void Number_Draw(float x, float y, int n);

#define NUMBER_WIDTH  (64)
#define NUMBER_HEIGHT (64)
#define NUMBER_PATTERN_MAX (10)

#endif