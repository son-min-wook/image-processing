#include <glut.h>
#include <math.h>
GLfloat scale = 1.0;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(0.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // load an identity matrix
	glColor3f(1, 0, 0);
	glViewport(0, 0, 250, 250);

	glutWireTeapot(scale);

	glViewport(0, 250, 250, 250);
	glRotatef(90, 1, 0, 0);
	glutWireTeapot(scale);
	glRotatef(-90, 1, 0, 0);
	glViewport(250, 0, 250, 250);
	glRotatef(90, 0, 1, 0);
	glutWireTeapot(scale);
	glRotatef(-90, 0, 1, 0);
	glViewport(250, 250, 250, 250);
	glRotatef(35, 1, 0, 0);
	glRotatef(-30, 0, 1, 0);
	glutWireTeapot(scale);
	glRotatef(30, 0, 1, 0);
	glRotatef(-35, 1, 0, 0);

	glFlush();
}
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog21: CAD");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
