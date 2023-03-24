#pragma once
#include <GL/freeglut.h>
#include <iostream>
#include <random>
#include "Global.h"
#include "Font.h"
class GameMain
{
	Font font;

	int Height;		//盤面縦
	int Width;		//盤面横

	int BombNum;	//爆弾数
	int** Stage = nullptr;	//盤面
	int** BombCount = nullptr;//爆弾数表示用
	int** Flag = nullptr;//フラグ

	int XSize;    //マス目の平均サイズ(X座標)
	int YSize;	 //マス目の平均サイズ(Y座標)

	bool GameFlag;					//ゲームオーバーとゲームクリアしたときにtrueにする用
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

