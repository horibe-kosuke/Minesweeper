#include "Result.h"

Result::Result()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = viewport[2] * 0.4f;
	y = viewport[3] * 0.4f;
}

Result::~Result()
{
}

void Result::Resize()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = viewport[2] * 0.4f;
	y = viewport[3] * 0.4f;
}

void Result::PassiveMotion(int x, int y)
{

	//RETRYにマウスがあるときRECTを赤色にする
	if (this->x - 150.0f <= x && this->x - 10.0f >= x && this->y + 100.0f <= y && this->y + 160.0f >= y) {
		PolygonColor[0][0] = 1.0f;
		PolygonColor[0][1] = 0.0f;
		PolygonColor[0][2] = 0.0f;

		PolygonColor[1][0] = 1.0f;
		PolygonColor[1][1] = 1.0f;
		PolygonColor[1][2] = 1.0f;

	}
	//EXITにマウスがあるときRECTを赤色にする
	else if(this->x + 150.0f <= x && this->x + 150.0f+140.0f >= x && this->y + 100.0f <= y && this->y + 160.0f >= y) {
		PolygonColor[1][0] = 1.0f;
		PolygonColor[1][1] = 0.0f;
		PolygonColor[1][2] = 0.0f;

		PolygonColor[0][0] = 1.0f;
		PolygonColor[0][1] = 1.0f;
		PolygonColor[0][2] = 1.0f;
	}
	else {
		PolygonColor[0][0] = 1.0f;
		PolygonColor[0][1] = 1.0f;
		PolygonColor[0][2] = 1.0f;

		PolygonColor[1][0] = 1.0f;
		PolygonColor[1][1] = 1.0f;
		PolygonColor[1][2] = 1.0f;
	}
}

int Result::Click(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {
			//RETRYをクリックしたとき
			if (this->x - 150.0f <= x && this->x - 10.0f >= x && this->y + 100.0f <= y && this->y + 160.0f >= y) {

				return GAMEMAIN;
			}
			//EXITをクリックしたとき
			else if (this->x + 150.0f <= x && this->x + 150.0f + 140.0f >= x && this->y + 100.0f <= y && this->y + 160.0f >= y) {
				return EXIT;
			}
		}
	}

	return 0;
}

void Result::GameClearDraw()
{
	//文字描画
	font.Begin();
	font.SetColor(0x00, 0xff, 0x00);
	font.SetPosition(x - 150.0f, y);
	font.SetSize(100.0f);
	font.SetScale(0.5f, 0.4f);
	font.Draw("GAME CLEAR");
	font.End();


	//glRectf(100,300,250,350);
	glColor3f(PolygonColor[0][0], PolygonColor[0][1], PolygonColor[0][2]);
	glRectf(x - 150, y + 100, x - 10, y + 160);
	font.Begin();
	font.SetColor(0x00, 0x00, 0x00);
	font.SetPosition(x - 150, y + 100);
	font.SetSize(100.0f);
	font.SetScale(0.3f, 0.3f);
	font.Draw("RETRY");
	font.End();

	glColor3f(PolygonColor[1][0], PolygonColor[1][1], PolygonColor[1][2]);
	glRectf(x + 150, y + 100, x + 150 + 140, y + 160);
	font.Begin();
	font.SetColor(0x00, 0x00, 0x00);
	font.SetPosition(x + 150 + 25, y + 100);
	font.SetSize(100.0f);
	font.SetScale(0.3f, 0.3f);
	font.Draw("EXIT");
	font.End();
}

void Result::GameOverDraw()
{
	//文字描画
	font.Begin();
	font.SetColor(0xff, 0x00, 0x00);
	font.SetPosition(x - 150.0f, y);
	font.SetSize(100.0f);
	font.SetScale(0.5f, 0.4f);
	font.Draw("GAME OVER");
	font.End();

	glColor3f(PolygonColor[0][0], PolygonColor[0][1], PolygonColor[0][2]);
	glRectf(x - 150, y + 100, x - 10, y + 160);
	font.Begin();
	font.SetColor(0x00, 0x00, 0x00);
	font.SetPosition(x - 150, y + 100);
	font.SetSize(100.0f);
	font.SetScale(0.3f, 0.3f);
	font.Draw("RETRY");
	font.End();

	glColor3f(PolygonColor[1][0], PolygonColor[1][1], PolygonColor[1][2]);
	glRectf(x + 150, y + 100, x + 150 + 140, y + 160);
	font.Begin();
	font.SetColor(0x00, 0x00, 0x00);
	font.SetPosition(x + 150 + 25, y + 100);
	font.SetSize(100.0f);
	font.SetScale(0.3f, 0.3f);
	font.Draw("EXIT");
	font.End();
}
