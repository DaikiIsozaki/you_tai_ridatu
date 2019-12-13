#ifndef DEBUG_PRIMITIVE_H
#define DEBUG_PRIMITIVE_H

void DebugPrimitive_Initialize(void);
void Debug_Primitive_Finalize(void);
void Debug_Primitive_BatchBegin(void);
void Debug_Primitive_BatchDrawCircle(float x,float y,float radius);
void Debug_Primitive_BatchRun(void);


#endif // !DEBUG_PRIMITIVE_H

