
#include <glut.h>
#include <math.h>
#include <stdlib.h>

void init();
void display();
void timer(int);

GLint day = 0.0;
static int delay = 1;

void main(int argc, char* argv[])
{
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Solar System");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);
	init();
	glutMainLoop();
}

void init()
{
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.0, 1.0, -1.0, 1.0, -5.0, 5.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(90, 1.0, 0.0, 0.0);             //making rotation axis

	glColor3f(1.0, 0.3, 0.3);
	glutWireSphere(0.2, 20, 16);          //sun


	glRotatef(5.5, 0.0, 1.0, 0.0);   //earth Revolution axis
	glRotatef((GLfloat)day / 365.0, 0.0, 0.0, -1.0);  //earth revolution

	glPushMatrix();
	glTranslatef(0.7, 0.0, 0.0);  //move eatvh location
	glRotatef((GLfloat)day / 365.0, 0.0, 0.0, 1.0);
	glRotatef(-23.5, 0.0, 1.0, 0.0);      //earth rotation axis
	glRotatef((GLfloat)day, 0.0, 0.0, -1.0);
	glColor3f(0.5, 0.6, 0.7);
	glutWireSphere(0.1, 10, 8);

	glRotatef((GLfloat)day / 30.0, 0.0, 0.0, -1.0);   //moon
	glPushMatrix();
	glTranslatef(0.2, 0.0, 0.0);
	glRotatef(23.5, 0.0, 1.0, 0.0);
	glRotatef((GLfloat)day, 0.0, 0.0, -1.0);
	glColor3f(0.9, 0.8, 0.2);
	glutWireSphere(0.04, 10, 8);
	glPopMatrix();
	glPopMatrix();
	glutSwapBuffers();

	glFlush();
}

void timer(int t)
{
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t); // set timer function
	day += 1;
}