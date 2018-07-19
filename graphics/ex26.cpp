#include <glut.h>
#include <math.h>
#include <stdlib.h>
#include <memory.h>
#define PI 3.141592

typedef struct _object
{
	GLfloat*        vertices;    
	GLfloat*        colors;     
	GLubyte*        indices;     
	int             nums;       

	GLfloat         theta[3];    
	GLfloat         trans[3];		

	struct _object* next;
	struct _object* child;
} Object;

typedef struct _viewer
{
	GLfloat         eye[3];  
	GLfloat         at[3];  
	GLfloat         up[3];  
} Viewer;

GLfloat vertices1[][3] = { { -0.6,-1.0,-0.05 },{ 0.6,-1.0,-0.05 },{ 0.6,1.0,-0.05 },{ -0.6,1.0,-0.05 },
{ -0.6,-1.0, 0.05 },{ 0.6,-1.0, 0.05 },{ 0.6,1.0, 0.05 },{ -0.6,1.0, 0.05 } };
GLfloat colors1[][4] = { { 0.0, 0.0, 0.0, 0.5 },{ 1.0, 0.0, 0.0, 0.5 },{ 1.0, 1.0, 0.0, 0.5 },{ 0.0, 1.0, 0.0, 0.5 },
{ 0.0, 0.0, 1.0, 0.5 },{ 1.0, 0.0, 1.0, 0.5 },{ 1.0, 1.0, 1.0, 0.5 },{ 0.0, 1.0, 1.0, 0.5 } };
GLubyte texflag[] = { 1, 0, 0, 0, 1, 0 };
GLubyte indices1[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };

Object box;
Viewer v;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-1.5, 1.5, -1.5, 1.5, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin()
{
	glutPostRedisplay();
}

void polygon(Object* p, int index)
{
	glBegin(GL_POLYGON);
	for (int i = 0; i<4; i++)
	{
		glColor4fv(&p->colors[p->indices[index * 4 + i] * 4]);
		glVertex3fv(&p->vertices[p->indices[index * 4 + i] * 3]);
	}
	glEnd();
}

void cube(Object* p)
{
	for (int i = 0; i<6; i++)
	{
		polygon(p, i);
	}
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') v.eye[0] -= 0.1; if (key == 'X') v.eye[0] += 0.1;
	if (key == 'y') v.eye[1] -= 0.1; if (key == 'Y') v.eye[1] += 0.1;
	if (key == 'z') v.eye[2] -= 0.1; if (key == 'Z') v.eye[2] += 0.1;
}

void draw(Object* p)
{

	glPushMatrix();


	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	cube(p);


	if (p->child) draw(p->child);

	glPopMatrix();

	if (p->next) draw(p->next);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glLoadIdentity();
	gluLookAt(v.eye[0], v.eye[1], v.eye[2], v.at[0], v.at[1], v.at[2], v.up[0], v.up[1], v.up[2]);


	draw(&box);

	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog31: Drawing a box");


	glutIdleFunc(spin);
	glutKeyboardFunc(keyboard_handler);
	glutDisplayFunc(display);

	box.vertices = &vertices1[0][0];
	box.colors = &colors1[0][0];
	box.indices = &indices1[0];
	box.nums = 24;

	box.theta[0] = box.theta[1] = box.theta[2] = 0;
	box.trans[0] = box.trans[1] = box.trans[2] = 0;
	box.next = 0;
	box.child = 0;


	v.eye[0] = 1.0; v.eye[1] = 1.0; v.eye[2] = 1.0;
	v.at[0] = 0.0; v.at[1] = 0.0; v.at[2] = 0.0;
	v.up[0] = 0.0; v.up[1] = 1.0; v.up[2] = 0.0;

	init();
	glutMainLoop();

	return 0;
}
