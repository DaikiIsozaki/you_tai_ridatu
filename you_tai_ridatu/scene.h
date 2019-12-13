#ifndef SCENE_H
#define SCENE_H

typedef enum 
{
	SCENE_INDEX_TITLE,
	SCENE_INDEX_GAME,
	SCENE_INDEX_Result,
	SCENE_INDEX_MAX,
}SCENE_INDEX;


void scene_Initialize(SCENE_INDEX index);
void scene_Finalize(void);
void scene_Update(void);
void scene_Draw(void);
void scene_Check(void);
void scene_Change(SCENE_INDEX index);


#endif // !SCENE_H


