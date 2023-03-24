#pragma once
#include <GL/freeglut.h>
#include <iostream>
#define FONT_DEFAULT_SIZE 100.0f

class Font 
{
	float Pos[2];	//位置
	float Size;		//文字サイズ
	float Scale[3];	//スケール
	float Color[3];	//色
public:
	Font();
	~Font();

	void Begin();
	void End();

	void SetPosition(float x, float y);
	void SetSize(float size);
	void SetScale(float x,float y);
	void SetColor(unsigned char red, unsigned char green, unsigned char blue);
	void Draw(const char* format, ...);
};

