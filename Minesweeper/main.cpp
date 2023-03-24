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
	//�F�w��
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGHT, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//�h��Ԃ�
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

	//���s
	glFlush();

	//�X���b�v�`�F�C��
	glutSwapBuffers();
}

void Resize(int w, int h) {
	//�r���[�|�[�g
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
	//�f�B�X�v���C�̕\�����[�h��ݒ�
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	//�E�B���h�E�T�C�Y
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//�E�B���h�E�ʒu
	glutInitWindowPosition(100, 100);

	//�E�B���h�E����
	glutCreateWindow("Minesweeper");

}



void Keyboard(unsigned char key, int x, int y) {
	printf("0x%x\n", key);

	//R�L�[
	if (key == 0x72) {
		//GameInit();
	}
	//ESC�L�[
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

	//GLUT������
	glutInit(&argc, argv);

	//������
	Init();

	//�L�[�{�[�h
	glutKeyboardFunc(Keyboard);

	glutMouseFunc(Mouse);

	glutMotionFunc(Motion);

	glutPassiveMotionFunc(PassiveMotion);
	//�r���[�|�[�g
	glutReshapeFunc(Resize);

	//�`��
	glutDisplayFunc(Display);

	glutIdleFunc(Idle);

	glutTimerFunc(10, Timer, 0);
	
	Title=new GameTitle();
	//���C�����[�v
	glutMainLoop();

	return 0;
}