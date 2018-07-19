#include <math.h>
#include <glut.h>

int delay = 20;
GLfloat angle = 0, toggle = 0;
GLfloat vertices1[][3] = { { -0.2,-1.0,-0.2 },{ 0.2,-1.0,-0.2 },{ 0.2,1.0,-0.2 },{ -0.2,1.0,-0.2 },
{ -0.2,-1.0, 0.2 },{ 0.2,-1.0, 0.2 },{ 0.2,1.0, 0.2 },{ -0.2,1.0, 0.2 } };
GLfloat colors1[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices1[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };
GLfloat vertices2[][3] = { { -0.8,-0.1,-0.1 },{ 0.8,-0.1,-0.1 },{ 0.8,0.1,-0.1 },{ -0.8,0.1,-0.1 },
{ -0.8,-0.1,0.1 },{ 0.8,-0.1,0.1 },{ 0.8,0.1,0.1 },{ -0.8,0.1,0.1 } };
GLfloat colors2[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices2[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };
GLfloat vertices3[][3] = { { -0.1,-0.4,-0.1 },{ 0.1,-0.4,-0.1 },{ 0.1,0.4,-0.1 },{ -0.1,0.4,-0.1 },
{ -0.1,-0.4,0.1 },{ 0.1,-0.4,0.1 },{ 0.1,0.4,0.1 },{ -0.1,0.4,0.1 } };
GLfloat colors3[][3] = { { 0.0, 0.0, 0.0 },{ 1.0, 0.0, 0.0 },{ 1.0,1.0, 0.0 },{ 0.0,1.0, 0.0 },
{ 0.0, 0.0, 1.0 },{ 1.0, 0.0, 1.0 },{ 1.0,1.0, 1.0 },{ 0.0,1.0, 1.0 } };
GLubyte indices3[] = { 0,3,2,1, 2,3,7,6, 0,4,7,3, 1,2,6,5, 4,5,6,7, 0,1,5,4 };
typedef struct _object
{
	GLfloat*        vertices;    
	GLfloat*        colors;      
	GLubyte*        indices;    
	int             nums;        
	GLfloat         theta[3];   
	GLfloat         trans[3];		
	struct _object* child;
	struct _object* next;
} Object;
typedef struct _window
{
	GLfloat left;
	GLfloat right;
	GLfloat bottom;
	GLfloat top;
	GLfloat near;
	GLfloat far;
} Window;
Window w = { -1,1,-1,1,-1,1 };



Object top, sb1, sb2, sb3;
GLfloat dir = 1.0;

void init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glClearColor(1.0, 1.0, 1.0, 1.0);
	glOrtho(-2.0, 2.0, -2.0, 2.0, -10.0, 10.0);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

GLfloat clip(GLfloat x)
{
	if (x < 0) return x + 360.0;
	if (x > 360.0) return x - 360.0;
	return x;
}

void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'z') {
		w.left--;
		w.right++;
		w.bottom--;
		w.top++;
		w.near--;
		w.far++;
	}
	if (key == 'Z') {
		if (w.left == 0) {}
		else {
			w.left++;
			w.right--;
			w.bottom++;
			w.top--;
			w.near++;
			w.far--;
		}
	}
	if (key == 'r') {
		if (toggle == 0) {
			toggle = 1;
		}
		else if (toggle == 1) {
			toggle = 0;
		}
	}
}

void mouse_handler(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON   && state == GLUT_DOWN) dir = -dir;
}

void draw(Object* p)
{
	glPushMatrix();
	glTranslatef(p->trans[0], p->trans[1], p->trans[2]);
	glRotatef(p->theta[0], 1.0, 0.0, 0.0);
	glRotatef(p->theta[1], 0.0, 1.0, 0.0);
	glRotatef(p->theta[2], 0.0, 0.0, 1.0);

	glVertexPointer(3, GL_FLOAT, 0, p->vertices);
	glColorPointer(3, GL_FLOAT, 0, p->colors);
	glDrawElements(GL_QUADS, p->nums, GL_UNSIGNED_BYTE, p->indices);
	if (p->child) {
		draw(p->child);
	}
	glPopMatrix();
	if (p->next) {

		draw(p->next);

	}
}

void display()
{
	GLfloat x, y;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(w.left, w.right, w.bottom, w.top, w.near, w.far);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glRotatef(angle, 1, 1, 0.0);
	for (y = -20; y <= 20; y += 4) {
		for (x = -20; x <= 20; x += 4) {
			glPushMatrix();
			glTranslatef(x, y, 0);
			draw(&top);
			glPopMatrix();
		
		}
	}
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{
	
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Prog30: Global transformation");

	glutKeyboardFunc(keyboard_handler);
	glutMouseFunc(mouse_handler);
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);

	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);

	top.vertices = &vertices1[0][0];
	top.colors = &colors1[0][0];
	top.indices = &indices1[0];
	top.nums = 24;
	top.theta[0] = top.theta[1] = top.theta[2] = 0;
	top.trans[0] = top.trans[1] = top.trans[2] = 0;

	top.child = &sb1;
	sb1.vertices = &vertices2[0][0];
	sb1.colors = &colors2[0][0];
	sb1.indices = &indices2[0];
	sb1.nums = 24;
	sb1.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb1.trans[0] = sb1.trans[2] = 0;
	sb1.trans[1] = 1.0;
	sb1.child = 0;
	sb1.next = &sb2;
	sb2.vertices = &vertices2[0][0];
	sb2.colors = &colors2[0][0];
	sb2.indices = &indices2[0];
	sb2.nums = 24;
	sb2.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb2.trans[0] = sb1.trans[2] = 0;
	sb2.trans[1] = -1.0;
	sb2.child = &sb3;
	sb2.next = 0;
	sb3.vertices = &vertices3[0][0];
	sb3.colors = &colors3[0][0];
	sb3.indices = &indices3[0];
	sb3.nums = 24;
	sb3.theta[0] = sb1.theta[1] = sb1.theta[2] = 0;
	sb3.trans[1] = sb1.trans[2] = 0;
	sb3.trans[0] = 0.8;
	sb3.child = 0;
	sb3.next = 0;
	init();
	glutMainLoop();

	return 0;
}
void timer(int t) {
	top.theta[2] += 2.0*dir;  top.theta[2] = clip(top.theta[2]);
	sb1.theta[2] += 4.0*dir;  sb1.theta[2] = clip(sb1.theta[2]);
	sb2.theta[2] += 4.0*dir;  sb2.theta[2] = clip(sb2.theta[2]);
	sb3.theta[2] += 5.0*dir;  sb3.theta[2] = clip(sb3.theta[2]);
	if (toggle == 1)
		angle++;
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);

}
