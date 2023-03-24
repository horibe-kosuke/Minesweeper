#pragma once
#include "Global.h"
#include "Font.h"
class Result
{
	Font font;
	int x;
	int y;

	float PolygonColor[2][3] = {
	{ 1.0f,1.0f,1.0f},
	{ 1.0f,1.0f,1.0f}
	};
public:
	Result();
	~Result();
	void Resize();
	void PassiveMotion(int x, int y);
	int Click(int button, int state, int x, int y);
	void GameClearDraw();
	void GameOverDraw();
};

