
#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <glut.h>
#include "ImageProc.h"

// ---------------------------------------------------------------------------------------------
// Globals
// ---------------------------------------------------------------------------------------------

ImageProc g_cImg;
int       g_qunt_step = 1;
int       g_qunt_stepTheta = 5;
float	  g_qunt_stepf = 1;


// ---------------------------------------------------------------------------------------------
// Initialize & Idle
// ---------------------------------------------------------------------------------------------

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void idle()
{
	glutPostRedisplay();
}

// ---------------------------------------------------------------------------------------------
// I/O
// ---------------------------------------------------------------------------------------------

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'g') g_cImg.convertToGray();
	if (key == 'z') g_cImg.convertToSepia();
	if (key == 'B') g_cImg.samplingBy2();
	if (key == 'q') { g_qunt_step *= 2; g_cImg.quantization(g_qunt_step); }
	if (key == 'o') { g_qunt_step = 1; g_cImg.loadFromBMP("taylor.bmp"); }
	if (key == 'k') g_cImg.Kuwahara();
	if (key == 'm') g_cImg.mirroring();
	if (key == 'h') g_cImg.histogram();  //
	if (key == 'e') g_cImg.embossing();
	if (key == 'n') g_cImg.noise();
	if (key == 'c') g_cImg.contrast();
	if (key == 'r') g_cImg.Blurring();
	if (key == 'i') g_cImg.Gaussian();
	if (key == 'S') g_cImg.sharpening();
	if (key == 't') g_cImg.smoothing();
	if (key == 'H') g_cImg.HSI();        
	if (key == 'K') g_cImg.kmean();      //
	if (key == 'C') g_cImg.compensation();   //

	if (key == 'U') { g_qunt_step *= 2; g_cImg.upscaling(g_qunt_step); }
	if (key == 'D') { g_qunt_step *= 2; g_cImg.downscaling(g_qunt_step); }
	if (key == 'R') { g_qunt_stepTheta *= 2; g_cImg.rotation(g_qunt_stepTheta); }
	if (key == 'G') { g_qunt_stepf *= 2; g_cImg.gamma(g_qunt_stepf); }
}

// ----------------------------------------------------------------------------------------------
// Display
// ---------------------------------------------------------------------------------------------
void Sprint(double x, double y, char *st) {
	int l, i;
	l = strlen(st);
	glRasterPos3f(x, y, -7.0);
	for (i = 0; i < l; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, st[i]);
	}


}
void bmenu() {
	int bmenu = 1;

}

void display()
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRasterPos3f(-2.0, -2.0, -8.0);

	glPixelZoom((GLfloat)glutGet(GLUT_WINDOW_WIDTH) / g_cImg.getWidth(), (GLfloat)glutGet(GLUT_WINDOW_HEIGHT) / g_cImg.getHeight());
	glDrawPixels(g_cImg.getWidth(), g_cImg.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, g_cImg.getRGB());
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{

	g_cImg.loadFromBMP("taylor.bmp");


	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(g_cImg.getWidth(), g_cImg.getHeight());
	glutCreateWindow("HW5");

	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	// texture initialization
	glEnable(GL_TEXTURE_2D);


	init();
	glutMainLoop();

	return 0;
}