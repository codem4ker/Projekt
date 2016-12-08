#include "myglwidget.h"
#include <QtOpenGL>

MyGLWidget::MyGLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
}

MyGLWidget::~MyGLWidget()
{
}

void MyGLWidget::initializeGL()
{
	glEnable(GL_TEXTURE_2D);
}

void MyGLWidget::paintGL()
{
	loadTexture();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindTexture(GL_TEXTURE_2D, texture);
	
	glBegin(GL_QUADS);
	// Front Face
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
															  // Back Face
	glEnd();


}

void MyGLWidget::resizeGL(int w, int h)
{
}

int MyGLWidget::loadTexture()
{
	int size = width * 3 * height;
	unsigned char* pixels = new unsigned char[size];
	
	drawCurve(pixels, 0.5, 0.5);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Filtering
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

void MyGLWidget::drawCurve(unsigned char* tab, double a, double b)
{
	for (double i = 0; i < 10; i += 0.1)
	{
		int x = (sin(a * i) + 1) * 250;
		int y = (sin(b * i) + 1) * 250;
		*(tab + y * this->width + 3 * x) = 255;
	}
}