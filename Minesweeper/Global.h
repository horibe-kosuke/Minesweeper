#pragma once
static float WINDOW_WIDTH = 640.0f;	//ウィンドウ横幅
static float WINDOW_HEIGHT = 480.0f;	//ウィンドウ縦幅

static int GameState = 0;

enum STATE {
	TITLE,
	GAMEMAIN,
	GAMECLEAR,
	GAMEOVER,
	EXIT
};