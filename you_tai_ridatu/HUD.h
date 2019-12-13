#ifndef HUD_H
#define HUD_H

void Hud_Init(void);
void Hud_Uninit(void);
void Hud_Update(void);
void Hud_Draw(void);

enum
{
	HUD_TYPE_ENEMY_NUM,
	HUD_TYPE_COA_NUM,
	HUD_TYPE_TIME,

	HUD_TYPE_MAX,
};

#endif // !HUD_H
#pragma once
