#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
void init();
void display();
float a[2] = { 0,0 }, b[2] = { 25,50 }, c[2] = { 50,0 };
int main(int argc, char* argv[])
{
	void triangle(float[], float[], float[], int);
	glutInit(&argc, (char**)argv);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog04: recursive triangles");
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void init()
{
	srand(time(0));
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glColor3f(1.0, 0.0, 0.0);
	gluOrtho2D(0.0, 50.0, 0.0, 50.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
void triangle(float a[], float b[], float c[], int t) {
	float x[2], y[2], z[2];
	if (t == 5) {
		glVertex2fv(a);
		glVertex2fv(b);
		glVertex2fv(c);
	}
	else {
		t = t + 1;
		x[0] = (b[0] + a[0]) / 2;
		x[1] = (b[1] + a[1]) / 2;
		y[0] = (b[0] + c[0]) / 2;
		y[1] = (b[1] + c[1]) / 2;
		z[0] = (c[0] + a[0]) / 2;
		z[1] = c[1];
		triangle(a, x, z, t);
		triangle(x, b, y, t);
		triangle(z, y, c, t);
	}
}
void display()
{
	glBegin(GL_TRIANGLES);
	triangle(a, b, c, 0);

	glEnd();
	glFlush();
}

