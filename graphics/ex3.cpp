#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void init();
void display();
static int delay = 1;//1
float x, y;
float xinc, yinc;
int main(int argc, char* argv[])
{
	srand(time(0));
	x = rand() % 50; y = rand() % 50;
	xinc = rand() % 200; yinc = rand() % 200;
	xinc /= 1000; yinc /= 1000;
	xinc -= 0.1; yinc -= 0.1;
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog03: bouncing pixel");
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
	glColor3f(x / 50, y / 50, 0.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	if (x < 0 || x > 50) {
		xinc = xinc * -1;
	}
	if (y < 0 || y > 50) {
		yinc = yinc * -1;
	}
	x += xinc;
	y += yinc;

	glEnd();
	glFlush();
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
