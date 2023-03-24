#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <random>
#include "Global.h"
#include "Font.h"
class GameMain
{
	Font font;

	int Height;		//�Ֆʏc
	int Width;		//�Ֆʉ�

	int BombNum;	//���e��
	int** Stage = nullptr;	//�Ֆ�
	int** BombCount = nullptr;//���e���\���p
	int** Flag = nullptr;//�t���O

	int XSize;    //�}�X�ڂ̕��σT�C�Y(X���W)
	int YSize;	 //�}�X�ڂ̕��σT�C�Y(Y���W)

	bool GameFlag;					//�Q�[���I�[�o�[�ƃQ�[���N���A�����Ƃ���true�ɂ���p
public:
	GameMain();
	~GameMain();

	void Init();

	void Resize();

	int Click(int button, int state, int x, int y);
	void RecursiveCall(int i, int j);
	void Draw();
	void StageDraw();
	bool GameClear();
	void GameOver();

};

