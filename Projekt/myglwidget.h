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
	int height = 593;
	int width = 691;
	int loadTexture();
	void drawCurve(unsigned char* tab, double a, double b);
	GLuint texture;

public slots:
	void blueButton();
	void greenButton();
	void redButton();

};
