#include "Font.h"

Font::Font()
{
	Pos[0] = 0.0f;
	Pos[1] = 0.0f;

	Size = 100.0f;

	Color[0] = 0xff;
	Color[1] = 0xff;
	Color[2] = 0xff;

	Scale[0] = 1.0f;
	Scale[1] = 1.0f;
	Scale[2] = 1.0f;
}

Font::~Font()
{
	Pos[0] = NULL;
	Pos[1] = NULL;
	Size = NULL;
}

void Font::Begin()
{
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, viewport[2], viewport[3], 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Font::End()
{
	glPopMatrix();
	glPopAttrib();
}

void Font::SetPosition(float x, float y)
{
	Pos[0] = x;
	Pos[1] = y;
}

void Font::SetSize(float size)
{
	Size = size;
}

void Font::SetScale(float x, float y)
{
	Scale[0]=x;
	Scale[1]=y;
}

void Font::SetColor(unsigned char red, unsigned char green, unsigned char blue)
{
	Color[0] = red;
	Color[1] = green;
	Color[2] = blue;
}

void Font::Draw(const char* format, ...)
{
	va_list arglist;
	va_start(arglist, format);
	char str[256] = {};
	vsprintf_s(str, format, arglist);
	va_end(arglist);

	glColor3ub(Color[0], Color[1], Color[2]);
	glPushMatrix();
	glTranslatef(Pos[0] + (Size * 0.1f), Pos[1] + (Size * 0.5f), 0);

	int s = Size / FONT_DEFAULT_SIZE;
	glScalef(s * Scale[0], -s * Scale[1], Scale[2]);
	for (char* p = str; *p != NULL; p++) {
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *p);
	}

	glPopMatrix();
}
