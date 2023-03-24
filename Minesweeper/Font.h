#pragma once
#include <GL/freeglut.h>
#include <iostream>
#define FONT_DEFAULT_SIZE 100.0f

class Font 
{
	float Pos[2];	//�ʒu
	float Size;		//�����T�C�Y
	float Scale[3];	//�X�P�[��
	float Color[3];	//�F
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

