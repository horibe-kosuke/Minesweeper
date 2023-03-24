#include "GameMain.h"

GameMain::GameMain()
{
	Height = 9;
	Width = 9;
	BombNum = 5;
	XSize = WINDOW_WIDTH / Width;
	YSize = WINDOW_HEIGHT / Height;
	Init();
}

GameMain::~GameMain()
{
	for (int i = 0; i < Height; i++) {
		delete[] Stage[i];
		delete[] BombCount[i];
		delete[] Flag[i];
	}
	delete Stage;
	delete BombCount;
	delete Flag;
}

void GameMain::Init()
{
	GameFlag = false;

	//ÉÅÉÇÉäämï€
	Stage = new int* [Height];
	BombCount = new int* [Height];
	Flag = new int* [Height];
	for (int i = 0; i < Height; i++) {
		Stage[i] = new int[Width];
		BombCount[i] = new int[Width];
		Flag[i] = new int[Width];
	}

	//îöíeÇÇ«Ç±Ç…Ç®Ç≠Ç©ÇÃóêêî
	std::random_device rnd;

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			Stage[i][j] = 0;
			Flag[i][j] = 0;
		}
	}

	for (int i = 0; i < BombNum; i++) {
		int x;
		int y;
		do {
			x = rnd() % Width;
			y = rnd() % Height;
		} while (Stage[y][x] == 2);
		Stage[y][x] = 2;
	}

	//îöíeêîÇÃï\é¶
	int bombcount = 0;
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {

			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					if (i + y >= 0 && i + y < Height && j + x >= 0 && j + x < Width) {
						if (Stage[i][j] == 2) {
							BombCount[i][j] = -1;
						}
						else if (Stage[i + y][j + x] == 2) {
							bombcount++;
						}
					}
				}
			}

			BombCount[i][j] = bombcount;
			bombcount = 0;
		}
	}

	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			printf("%d", Stage[i][j]);
		}
		printf("\n");
	}
}

void GameMain::Resize()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	XSize = viewport[2] /Width;
	YSize = viewport[3] /Height;
}

int GameMain::Click(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {
			//printf("x:%d	y:%d\n", x, y);

			for (int i = 0; i < Height; i++) {
				for (int j = 0; j < Width; j++) {
					if (x >= (XSize)*j && x <= (XSize) * (j + 1)) {
						if (y >= (YSize)*i && y <= (YSize) * (i + 1)) {
							if (Stage[i][j] == 2) {
								Stage[i][j] = 2;
								return GAMEOVER;
								break;
							}
							else {
								Stage[i][j] = 1;
								if (GameClear() == true){
									return GAMECLEAR;
								}
							}
						}
					}
				}
			}


		}
		break;

	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_UP) {
			//printf("RIGHT_UP");
			for (int i = 0; i < Height; i++) {
				for (int j = 0; j < Width; j++) {
					if (x >= (XSize)*j && x <= (XSize) * (j + 1)) {
						if (y >= (YSize)*i && y <= (YSize) * (i + 1)) {
							if (Flag[i][j] == 0 && (Stage[i][j] == 0 || Stage[i][j] == 2)) {
								Flag[i][j] = 3;
								if (GameClear() == true) {
									return GAMECLEAR;
								}
							}
							else if (Flag[i][j] == 3) {
								Flag[i][j] = 0;
							}
						}
					}
				}
			}
		}
		break;
	}
	return -1;
}

void GameMain::RecursiveCall(int i, int j)
{
	if (Stage[i][j] == 2) {
		return;
	}



	if (BombCount[i][j] == 0) {
		BombCount[i][j] = -1;
		for (int y = -1; y <= 1; y++) {
			if (i + y < 0 || i + y >= Height) {
				continue;
			}
			for (int x = -1; x <= 1; x++) {
				if (j + x < 0 || j + x >= Width) {
					continue;
				}
				RecursiveCall(i + y, j + x);


			}
		}

	}

	//äJÇ¢ÇƒÇ¢ÇÈèÛë‘Ç…Ç∑ÇÈ
	Stage[i][j] = 1;
	return;
}

void GameMain::Draw()
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {

			if (Flag[i][j] == 3) {
				//ï∂éöï`âÊ
				font.Begin();
				font.SetColor(0xff, 0x00, 0x00);
				font.SetPosition(XSize * j, YSize * i);
				font.SetSize(100.0f);
				font.SetScale(0.5f, 0.4f);
				font.Draw("F");
				font.End();

			}
			else if (Stage[i][j] == 1) {
				RecursiveCall(i, j);

				//äJÇ¢ÇƒÇ¢ÇÈÇ∆Ç±ÇÎÇÕï`âÊ
				glBegin(GL_POLYGON);
				glColor3f(0.0f, 1.0f, 0.0f);
				glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i);
				glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i + YSize);
				glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i + YSize);
				glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i);
				glEnd();

				//ï∂éöï`âÊ
				font.Begin();
				font.SetColor(0x00, 0x00, 0x00);
				font.SetPosition(XSize * j, YSize * i);
				font.SetSize(100.0f);
				font.SetScale(0.5f, 0.4f);

				if (BombCount[i][j] != -1) {
					font.Draw("%d", BombCount[i][j]);
				}
				font.End();

			}
			else if (Stage[i][j] == 2) {
				if (GameFlag == true) {
					glBegin(GL_POLYGON);

					glColor3f(1.0f, 0.0f, 0.0f);
					glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i);
					glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i + YSize);
					glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i + YSize);
					glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i);

					glEnd();
				}
			}


		}
	}
}

void GameMain::StageDraw()
{
	//î’ñ ï\é¶
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			glBegin(GL_LINE_LOOP);

			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i);
			glVertex2d((GLdouble)XSize * j, (GLdouble)YSize * i + YSize);
			glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i + YSize);
			glVertex2d((GLdouble)XSize * j + XSize, (GLdouble)YSize * i);

			glEnd();
		}
	}
}

bool GameMain::GameClear()
{
	int count = 0;
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {
			if (Stage[i][j] == 1) {
				count++;
			}
			else if (Stage[i][j] == 2) {
				if (Flag[i][j] == 3) {
					count++;
				}
				else {
					count++;
				}
			}
		}
	}

	if (Height * Width == count) {
		GameFlag = true;
		for (int i = 0; i < Height; i++) {
			for (int j = 0; j < Width; j++) {
				if (Flag[i][j] == 3) {
					Flag[i][j] = 0;
					Stage[i][j] = 2;
				}
			}
		}
		printf("CLEAR\n");
		return true;
	}

	return false;
}

void GameMain::GameOver()
{
	for (int i = 0; i < Height; i++) {
		for (int j = 0; j < Width; j++) {


			if (Stage[i][j] == 0) {
				Stage[i][j] = 1;
			}

		}
	}
}
