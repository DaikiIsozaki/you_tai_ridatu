
#include "common.h"
#include "sprite.h"
#include "texture.h"
#include "number.h"

static int g_Digit = 0;
static int g_CounterStopValue = 0;

void Score_Initialize(int digit)
{
	Number_Initialize();

	g_Digit = digit;

	g_CounterStopValue = 1;
	for (int i = 0; i < digit; i++)
	{
		g_CounterStopValue *= 10;
	}
	g_CounterStopValue--;
}

void Score_Finalize(void)
{
	Number_Finalize();
}

void Score_Draw(float x, float y, int score, bool bZero, bool bLeft)
{
	if (bLeft)
	{
		int num = score;
		int cnt = 0;
		do
		{
			num /= 10;
			cnt++;
		} while (num != 0);

		g_Digit = cnt;
	}

	for (int i = g_Digit - 1; i >= 0;i--)
	{
		//カンスト処理
		if (score > g_CounterStopValue)
		{
			score = g_CounterStopValue;
		}

		int n = score % 10;

		if (!bZero && (i != g_Digit - 1) && bLeft)
		{
			if (score == 0)
				return;
		}

		if (i != g_Digit - 1)
		{
			Number_Draw(x + NUMBER_WIDTH * i, y, n);
		}
		score /= 10;
	}
}

void Score_Draw2(float x, float y, int score, bool bZero, bool bLeft)
{
	if (bLeft)
	{
		int num = score;
		int cnt = 0;
		do
		{
			num /= 10;
			cnt++;
		} while (num != 0);

		g_Digit = cnt;
	}

	for (int i = g_Digit - 1; i >= 0;i--)
	{
		//カンスト処理
		if (score > g_CounterStopValue)
		{
			score = g_CounterStopValue;
		}

		int n = score % 10;

		if (!bZero && (i != g_Digit - 1) && bLeft)
		{
			if (score == 0)
				return;
		}

		Number_Draw(x + NUMBER_WIDTH * i, y, n);

		score /= 10;
	}
}

void Score_Draw3(float x, float y, int score, int fig, bool bLeft, bool bZero)
{
	//カンスト用の最大数値を作る
	int count_stop_score = 1;
	for (int i = 0; i < fig; i++)
	{
		count_stop_score *= 10;
	}

	if (score >= count_stop_score)
	{
		score = count_stop_score - 1;
	}

	if (bZero)
	{
		for (int i = 0; i < fig; i++)
		{
			//x+NUMBER_WIDTH*(fig-(i+1))
			int n = score % 10;
			score /= 10;
			Number_Draw(x + NUMBER_WIDTH*(fig - (i + 1)), y, n);
		}
	}
}