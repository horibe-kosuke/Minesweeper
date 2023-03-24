#pragma once
#include "Global.h"
#include "Font.h"


class GameTitle
{
	Font font;
	int x;
	int y;

	float PolygonColor[3]={1.0f,1.0f,1.0f};
public:
	GameTitle();
	~GameTitle();
	void Resize();
	void PassiveMotion(int x,int y);
	bool Click(int button, int state, int x, int y);
	void Draw();
};

