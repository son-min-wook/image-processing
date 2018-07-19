#include <glut.h>
#include <math.h>
#define PI 3.141592
void init();
void display();
int delay = 10;
int angle = 0;
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	glutCreateWindow("Prog11: 3D cube location");
	void timer(int);
	glutTimerFunc(delay, timer, 0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();

	return 0;
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0);
	glEnable(GL_DEPTH_TEST);
}

void display()
{
	GLfloat v[8][3] = { 15, 15, 35 , 35, 15, 35 , 35, 35, 35 , 15, 35, 35, 40, 20, 15 , 20, 20, 15 , 40, 40, 15 , 20, 40, 15 };
	int i;
	for (i = 0; i < 8; i++) {
		v[i][0] = (cos(PI*angle / 180)*v[i][0]) + (sin(PI*angle / 180)*v[i][2]);
		v[i][1] = v[i][1];
		v[i][2] = (v[i][0] * -sin(PI*angle / 180)) + cos(PI*angle / 180)*v[i][2];
	}
	angle++;
	angle %= 360;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();

	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[1]); glVertex3fv(v[4]); glVertex3fv(v[5]);
	glEnd();

	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[5]); glVertex3fv(v[4]); glVertex3fv(v[6]); glVertex3fv(v[7]);
	glEnd();

	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[7]); glVertex3fv(v[6]); glVertex3fv(v[2]); glVertex3fv(v[3]);
	glEnd();

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[0]); glVertex3fv(v[5]); glVertex3fv(v[7]); glVertex3fv(v[3]);
	glEnd();

	glColor3f(1.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3fv(v[1]); glVertex3fv(v[4]); glVertex3fv(v[6]); glVertex3fv(v[2]);
	glEnd();

	glFlush();
}
void timer(int t) {

	glutPostRedisplay();

	glutTimerFunc(delay, timer, t);

}
