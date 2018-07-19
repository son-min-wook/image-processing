#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void init();
void display();
static int delay = 100;
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog02: Random boxes");
	glutTimerFunc(delay, timer, 0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void display()
{
	int x1, y1, x2, y2, r, g, b;
	x1 = rand() % 50; y1 = rand() % 50; x2 = rand() % 50; y2 = rand() % 50;
	r = rand() % 256; g = rand() % 256; b = rand() % 256;
	glColor3f((GLfloat)r / 255, (GLfloat)g / 255, (GLfloat)b / 255);
	glBegin(GL_POLYGON);
	glVertex2f(x1, y1); glVertex2f(x1, y2);
	glVertex2f(x2, y2); glVertex2f(x2, y1);
	glEnd();
	glFlush();
}
void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
