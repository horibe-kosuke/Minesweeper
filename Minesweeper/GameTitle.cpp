#include "GameTitle.h"

GameTitle::GameTitle()
{
}

GameTitle::~GameTitle()
{
}

void GameTitle::Resize()
{
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	x = viewport[2] * 0.4f;
	y = viewport[3] * 0.4f;
}

void GameTitle::PassiveMotion(int x, int y)
{

	if (this->x <= x && this->x + 160.0f >= x && this->y <= y && this->y + 70.0f >= y) {
		PolygonColor[0] = 0.0f;
		PolygonColor[1] = 1.0f;
		PolygonColor[2] = 0.0f;
	}
	else {
		PolygonColor[0] = 1.0f;
		PolygonColor[1] = 1.0f;
		PolygonColor[2] = 1.0f;
	}
}

bool GameTitle::Click(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_UP) {
			if (this->x <= x && this->x + 160.0f >= x && this->y <= y && this->y + 70.0f >= y) {

				return true;
			}
		}
	}

	return false;
}

void GameTitle::Draw()
{


	glBegin(GL_POLYGON);
	glColor3f(PolygonColor[0], PolygonColor[1], PolygonColor[2]);
	glVertex2d((GLdouble)x, (GLdouble)y);
	glVertex2d((GLdouble)x + 160.0f, (GLdouble)y);
	glVertex2d((GLdouble)x + 160.0f, (GLdouble)y + 70.0f);
	glVertex2d((GLdouble)x, (GLdouble)y + 70.0f);
	glEnd();

	//•¶Žš•`‰æ
	font.Begin();
	font.SetColor(0x00, 0x00, 0x00);
	font.SetPosition(x, y);
	font.SetSize(100.0f);
	font.SetScale(0.5f, 0.4f);
	font.Draw("Start");
	font.End();

	//•¶Žš•`‰æ
	font.Begin();
	font.SetColor(0xff, 0x00, 0x00);
	font.SetPosition(x-150.0f, y-100.0f);
	font.SetSize(100.0f);
	font.SetScale(0.5f, 0.4f);
	font.Draw("MINESWEEPER");
	font.End();

}
