#include <glut.h>
void init();
void display();
int main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog01: first OpenGL program");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void init()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	for (double f = 10; f<40; f += 0.1)
	{
		glVertex2f(f, 10); glVertex2f(f, 40);
		glVertex2f(10, f); glVertex2f(40, f);
	}
	glEnd();
	glFlush();
}
