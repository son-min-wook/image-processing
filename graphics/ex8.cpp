#include <glut.h>
#include <math.h>

#define PI 3.141592
void init();
void display();

int main(int argc, char* argv[])
{

	glutInit(&argc, (char**)argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(500, 500);

	glutCreateWindow("Prog09: sphere");

	glutDisplayFunc(display);

	init();

	glutMainLoop();
	return 0;
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glOrtho(0.0, 50.0, 0.0, 50.0, -50.0, 50.0);
	glEnable(GL_DEPTH_TEST);
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 0.0);
}
void display()
{
	float i, j;
	int n, m, l;
	float x, y, z;
	float point[3][19][9];
	float pin[3][2];

	pin[0][0] = 25;
	pin[1][0] = 25;
	pin[2][0] = 5;
	pin[0][1] = 25;
	pin[1][1] = 25;
	pin[2][1] = 45;

	for (i = -180; i <= 180; i = i + 20) {
		for (j = -80; j <= 80; j = j + 20) {
			n = (i + 180) / 20;
			m = (j + 80) / 20;
			x = sin((i*PI) / 180) * cos((j*PI) / 180) * 20;
			y = cos((i*PI) / 180) * cos((j*PI) / 180) * 20;
			z = sin((j*PI) / 180) * 20;
			point[0][n][m] = floor((x + 25) * 100) / 100;
			point[1][n][m] = floor((y + 25) * 100) / 100;
			point[2][n][m] = floor((z + 25) * 100) / 100;

		}
	}
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(pin[0][0], pin[1][0], pin[2][0]);
	l = 9;
	for (n = 0; n < 19; n++) {

		glVertex3f(point[0][n][0], point[1][n][0], point[2][n][0]);
		if (n - l > 0)
			glColor3f((float)(n - l) / 9, 0.0, 0.0);
		else
			glColor3f((float)(n - l) / -9, 0.0, 0.0);
	}
	glEnd();
	glBegin(GL_QUAD_STRIP);
	for (m = 0; m < 8; m++) {
		for (n = 0; n < 19; n++) {
			if (n - l > 0)
				glColor3f((float)(n - l) / 9, 0.0, 0.0);
			else
				glColor3f((float)(n - l) / -9, 0.0, 0.0);
			glVertex3f(point[0][n][m], point[1][n][m], point[2][n][m]);
			glVertex3f(point[0][n][m + 1], point[1][n][m + 1], point[2][n][m + 1]);
		}
	}
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(pin[0][1], pin[1][1], pin[2][1]);
	for (n = 0; n < 19; n++) {

		glVertex3f(point[0][n][8], point[1][n][8], point[2][n][8]);
		if (n - l > 0)
			glColor3f((float)(n - l) / 9, 0.0, 0.0);
		else
			glColor3f((float)(n - l) / -9, 0.0, 0.0);
	}
	glEnd();
	glFlush();
}
