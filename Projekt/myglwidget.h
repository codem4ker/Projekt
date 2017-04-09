#pragma once

#include <QGLWidget>
#include <gl/GLU.h>
#include <thread>

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
	int height = 768;
	int width = 768;
	int pixmapSize;
	int a = 3;
	int b = 4;
	int fi = 0;
	unsigned char* pixels;
	GLuint texture;

	int loadTexture();

public slots:
	void setA(int value);
	void setB(int value);
	void setFi(int value);
};
