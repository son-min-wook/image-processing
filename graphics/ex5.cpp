#include <glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void init();

void display();

static int delay = 1;

float x[3], y[3];

float xinc[3], yinc[3];

int main(int argc, char* argv[])

{
	int i;
	srand(time(0));
	for (i = 0; i < 3; i++) {
		x[i] = rand() % 50; y[i] = rand() % 50;

		xinc[i] = rand() % 200; yinc[i] = rand() % 200;

		xinc[i] /= 1000; yinc[i] /= 1000;

		xinc[i] -= 0.1; yinc[i] -= 0.1;
	}
	void timer(int);

	glutInit(&argc, (char**)argv);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Prog06: bouncing triangle");

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
	glClear(GL_COLOR_BUFFER_BIT);

	int i;

	glColor3f(x[0] / 50, y[0] / 50, 0.0);

	glBegin(GL_TRIANGLES);

	for (i = 0; i < 3; i++) {
		glVertex2f(x[i], y[i]);

		if (x[i] < 0 || x[i] > 50) {

			xinc[i] = xinc[i] * -1;

		}

		if (y[i] < 0 || y[i] > 50) {

			yinc[i] = yinc[i] * -1;

		}

		x[i] += xinc[i];

		y[i] += yinc[i];

	}

	glEnd();

	glFlush();

}

void timer(int t) {

	glutPostRedisplay();

	glutTimerFunc(delay, timer, t);

}
