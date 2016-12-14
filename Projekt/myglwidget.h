#pragma once

#include <QGLWidget>
#include <gl/GLU.h>

class MyGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit MyGLWidget(QWidget* parent = 0);
	~MyGLWidget();

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:
	int color = 1;
	int height = 768;
	int width = 768;
	int pixmapSize;
	int a = 3;
	int b = 4;
	double dt = 0.0001;
	unsigned char* pixels;
	GLuint texture;

	int loadTexture();
	void drawCurve(unsigned char* tab, int a, int b);
	int nwd(int a, int b);
	int nww(int a, int b);

public slots:
	void blueButton();
	void greenButton();
	void redButton();
	void setA(int value);
	void setB(int value);
};
