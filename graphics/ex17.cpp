#include <glut.h>
#include <math.h>
GLfloat vertices[][3] = { { -1.0,-1.0,-1.0 },{ 1.0,-1.0,-1.0 },{ 1.0,1.0,-1.0 },{ -1.0,1.0,-1.0 },
{ -1.0,-1.0, 1.0 },{ 1.0,-1.0, 1.0 },{ 1.0,1.0, 1.0 },{ -1.0,1.0, 1.0 } };
GLfloat colors[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLfloat scale = 1.0;
GLint axis = 1;
GLdouble eye[3] = { 3,3,3 };
GLdouble at[3] = { 0,0,0 };
GLdouble up[3] = { 0,1,0 };
int delay = 20;
int type = 1;
void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	GLubyte indices[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); // load an identity matrix
	gluLookAt(eye[0], eye[1], eye[2], at[0], at[1], at[2], up[0], up[1], up[2]);
	glScaled(scale, scale, scale);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);
	glFlush();
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'x') { eye[0] -= 0.01; }
	if (key == 'X') { eye[0] += 0.01; }
	if (key == 'y') { eye[1] -= 0.01; }
	if (key == 'Y') { eye[1] += 0.01; }
	if (key == 'z') { eye[2] -= 0.01; }
	if (key == 'Z') { eye[2] += 0.01; }
	if (key == 'p') {
		if (type == 1) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
			glEnable(GL_DEPTH_TEST);
			glMatrixMode(GL_MODELVIEW);
			type = 2;
		}
		else {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glClearColor(1.0, 1.0, 1.0, 1.0);
			glFrustum(-2.0, 2.0, -2.0, 2.0, 2.0, 20.0);
			glEnable(GL_DEPTH_TEST);
			glMatrixMode(GL_MODELVIEW);
			type = 1;
		}
	}
}
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog20: perspective projection");
	glEnableClientState(GL_COLOR_ARRAY); // notify to use color array
	glEnableClientState(GL_VERTEX_ARRAY); // notify to use vertex array
	glVertexPointer(3, GL_FLOAT, 0, vertices); // set vertex array pointer
	glColorPointer(3, GL_FLOAT, 0, colors); // set color array pointer
	glutTimerFunc(delay, timer, 0);
	glutKeyboardFunc(keyboard_handler); // add keyboard handler
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}
