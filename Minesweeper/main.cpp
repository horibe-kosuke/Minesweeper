#include <iostream>
#include <GL/freeglut.h>
#include <random>
#include "GameTitle.h"
#include "GameMain.h"
#include "Result.h"
#include "Font.h"


GameTitle* Title;
GameMain* gamemain;
Result* result;



void Display() {
	//色指定
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//塗りつぶし
	glClear(GL_COLOR_BUFFER_BIT);

	switch (GameState) {
	case TITLE:
		Title->Draw();
		break;
	case GAMEMAIN:
		gamemain->Draw();
		gamemain->StageDraw();
		break;
	case GAMECLEAR:
		result->GameClearDraw();
		break;
	case GAMEOVER:
		result->GameOverDraw();
		break;
	}

	//実行
	glFlush();

	//スワップチェイン
	glutSwapBuffers();
}

void Resize(int w, int h) {
	//ビューポート
	glViewport(0, 0, w, h);

	WINDOW_WIDTH = (float)w;
	WINDOW_HEIGHT = (float)h;

	switch (GameState) {
	case TITLE:
		Title->Resize();
		break;

	case GAMEMAIN:
		gamemain->Resize();
		break;

	case GAMECLEAR:
	case GAMEOVER:
		result->Resize();
		break;
	}

}


void Init() {
	//ディスプレイの表示モードを設定
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//ウィンドウサイズ
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//ウィンドウ位置
	glutInitWindowPosition(100, 100);

	//ウィンドウ生成
	glutCreateWindow("Minesweeper");

}



void Keyboard(unsigned char key, int x, int y) {
	printf("0x%x\n", key);

	//Rキー
	if (key == 0x72) {
		//GameInit();
	}
	//ESCキー
	if (key == 0x1b) {
		exit(0);
	}

}

void Mouse(int button, int state, int x, int y) {
	int result;
	switch (GameState) {
	case TITLE:
		if (Title->Click(button, state, x, y)) {
			gamemain = new GameMain();
			gamemain->Resize();
			delete Title;
			Title=nullptr;
			GameState = 1;
		}
		break;
	case GAMEMAIN:
		result = gamemain->Click(button, state, x, y);

		if (result == GAMECLEAR) {
			GameState = GAMECLEAR;
			delete gamemain;
			gamemain=nullptr;
			::result=new Result();
			::result->Resize();
		}
		else if (result == GAMEOVER) {
			GameState = GAMEOVER;
			delete gamemain;
			gamemain = nullptr;
			::result = new Result();
			::result->Resize();
		}
		break;
	case GAMECLEAR:
	case GAMEOVER:
		result = ::result->Click(button, state, x, y);
		if (result == GAMEMAIN) {
			if (gamemain == nullptr) {
				gamemain = new GameMain();
				gamemain->Resize();
			}
			delete ::result;
			::result=nullptr;
			GameState = GAMEMAIN;
		}
		else if (result == EXIT) {
			if (::result != nullptr) {
				delete ::result;
				::result = nullptr;
			}
			exit(0);
		}
		break;
	}
}

void Motion(int x, int y) {

}

void PassiveMotion(int x, int y) {
	//printf("X = %d : Y = %d\n", x, y);


	switch (GameState) {
	case TITLE:
		Title->PassiveMotion(x, y);
		break;
	case GAMEMAIN:
		break;
	case GAMECLEAR:
		result->PassiveMotion(x, y);
		break;
	case GAMEOVER:
		result->PassiveMotion(x, y);
		break;
	}
}

void Timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(10, Timer, 0);
}
void Idle() {


}

int main(int argc, char* argv[]) {

	//GLUT初期化
	glutInit(&argc, argv);

	//初期化
	Init();

	//キーボード
	glutKeyboardFunc(Keyboard);

	glutMouseFunc(Mouse);

	glutMotionFunc(Motion);

	glutPassiveMotionFunc(PassiveMotion);
	//ビューポート
	glutReshapeFunc(Resize);

	//描画
	glutDisplayFunc(Display);

	glutIdleFunc(Idle);

	glutTimerFunc(10, Timer, 0);
	
	Title=new GameTitle();
	//メインループ
	glutMainLoop();

	return 0;
}