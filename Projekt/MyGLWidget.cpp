#include "myglwidget.h"
#include <QtOpenGL>

MyGLWidget::MyGLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	pixmapSize = width * 3 * height;
	pixels = new unsigned char[pixmapSize];
}

MyGLWidget::~MyGLWidget()
{
	free(pixels);
}

void MyGLWidget::initializeGL()
{
	glViewport(0, 0, 768, 768);
	glEnable(GL_TEXTURE_2D);
}

void MyGLWidget::paintGL()
{
	loadTexture();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);
	
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); 
	glVertex3f(-1.0f, -1.0f, 0.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); 
	glVertex3f(1.0f, -1.0f, 0.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); 
	glVertex3f(1.0f, 1.0f, 0.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); 
	glVertex3f(-1.0f, 1.0f, 0.0f);  // Top Left Of The Texture and Quad
															  // Back Face
	glEnd();


}

void MyGLWidget::resizeGL(int w, int h)
{
}

int MyGLWidget::loadTexture()
{
	memset(pixels, 0, pixmapSize);

	drawCurve(pixels, a, b);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	
	return 1;
}

void MyGLWidget::blueButton()
{
	color = 0;
	repaint();
}

void MyGLWidget::greenButton()
{
	color = 1;
	repaint();
}

void MyGLWidget::redButton()
{
	color = 2;
	repaint();
}

void MyGLWidget::setA(int value)
{
	this->a = value;
	repaint();
}

void MyGLWidget::setB(int value)
{
	this->b = value;
	repaint();
}

int MyGLWidget::nwd(int a, int b)
{
	if (b == 0) return a;
	nwd(b, a - b * floor(a/b));
}

int MyGLWidget::nww(int a, int b)
{ 
	return a * b / nwd(a, b);
}

void MyGLWidget::drawCurve(unsigned char* tab, int a, int b)
{
	double x;
	if (a == 0 && b == 0) x = dt;
	else if (a == 0) x = 2 * M_PI / b;
	else if (b == 0) x = 2 * M_PI / a;
	else if (a < b) x = 2 * M_PI * b;
	else x = 2 * M_PI * a;

	for (double i = 0; i <= x ; i += dt)
	{
		int x = (sin(a * i) + 1) * 374 + 5;
		int y = (sin(b * i) + 1) * 374 + 5;
		*(tab +  y * 3 * this->width + 3 * x + color) = 255;
	}
}