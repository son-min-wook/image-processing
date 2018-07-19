#include <math.h>
#include <glut.h>
#include <stdio.h>
#define PI 3.141592
GLfloat eye1 = 0, eye2 = 0, eye3 = 0, at1 = 0, at2 = 0, at3 = 2;   //gluLookAt elements
GLfloat beye1 = 0, beye2 = 0, beye3 = 0;         //previous gluLookAt's eye location. before of b
int delay = 20;
int ViewX = 0, ViewY = 0;          // location of mouse  (window Coordinate system)
int bViewX = 0, bViewY = 0;             //previous location of mouse (window Coordinate system)
GLfloat theta1 = 0, theta2 = 0;                //theta1: angle of x axis, theta2: angle of Y axis
void init() {
	glMatrixMode(GL_PROJECTION);
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glFrustum(-1, 1, -1, 1, 1, 20);                 //Perspective coordinate system
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(eye1, eye2, eye3, at1, at2, at3, 0, 1, 0);     //user's view point
	glPushMatrix();                //pot1 
	glTranslatef(0, 0, 2);
	glColor3f(0.0, 0, 1);
	glutWireTeapot(0.7);
	glPopMatrix();
	glPushMatrix();               //pot2
	glTranslatef(0, 0, -2);
	glColor3f(1.0, 0.0, 0.5);
	glutWireTeapot(0.7);
	glPopMatrix();
	glPushMatrix();               //pot3
	glTranslatef(2, 0, 0);
	glColor3f(0.0, 2.0, 1.5);
	glutWireTeapot(0.7);
	glPopMatrix();
	glPushMatrix();                 //pot4
	glTranslatef(-2, 0, 0);
	glColor3f(1.0, 1.0, 0.5);
	glutWireTeapot(0.7);
	glPopMatrix();
	glFlush();
}
void MyMouseMove(GLint X, GLint Y) {          //Only move the gaze at the current position
	if (bViewX == 0 && bViewY == 0) {    //for the first mouse click, there is no previous mouse location data
		ViewX = X;
		bViewX = X;
		ViewY = Y;
		bViewY = Y;
	}
	else {                             //not a fist mouse click
		ViewX = X;
		ViewY = Y;
		theta1 = theta1 - ((ViewX - bViewX));          //x axis angle
		theta2 = theta2 - ((ViewY - bViewY));       //y axis angle       Match movement of mouse with movement of eyes
		if (theta1>360)
			theta1 -= 360;
		if (theta2>90)
			theta2 = 90;
		if (theta1<-360)
			theta1 += 360;
		if (theta2<-90)
			theta2 = -90;
		bViewX = ViewX;
		bViewY = ViewY;
		at1 = eye1 + sin((theta1 * PI) / 180);              //change  x location
		at2 = eye2 + sin((theta2 * PI) / 180);           //change y location
		at3 = eye3 + cos(((360 - theta1) * PI) / 180);       //cahnge z location
		beye1 = eye1;
		beye2 = eye2;
		beye3 = eye3;
	}
}
void keyboard_handler(unsigned char key, int x, int y)
{
	if (key == 'w') {                    //go forward
		eye3 = eye3 + 0.05*cos((theta1*PI) / 180);
		eye1 = eye1 + 0.05*sin((theta1*PI) / 180);
		at3 = at3 + 0.05*cos((theta1*PI) / 180);
		at1 = at1 + 0.05*sin((theta1*PI) / 180);
	}
	else if (key == 's') {                   //go back
		eye1 -= 0.05*sin((theta1 * PI) / 180);
		eye3 -= 0.05*cos((theta1 * PI) / 180);
		at1 -= 0.05*sin((theta1 * PI) / 180);
		at3 -= 0.05*cos((theta1 * PI) / 180);
	}
	else if (key == 'a') {                         //go left
		eye1 += 0.05*sin(((theta1 + 90) * PI) / 180);
		eye3 += 0.05*cos(((theta1 + 90)  * PI) / 180);
		at1 += 0.05*sin(((theta1 + 90)  * PI) / 180);
		at3 += 0.05*cos(((theta1 + 90)  * PI) / 180);
	}
	else if (key == 'd') {                              //go right
		eye1 -= 0.05*sin(((theta1 + 90)  * PI) / 180);
		eye3 -= 0.05*cos(((theta1 + 90)  * PI) / 180);
		at1 -= 0.05*sin(((theta1 + 90)  * PI) / 180);
		at3 -= 0.05*cos(((theta1 + 90)  * PI) / 180);
	}
}
void mouse_handler(int btn, int state, int x, int y) {                  //If you turn your eye with the mouse and click again or move 
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {               //the position and turn your eyes with the mouse, it will not
		if (beye1 != eye1 || beye2 != eye2 || beye3 != eye3) {       //match the coordinates of the previous mouse and need to be reset.
			bViewX = 0;
			bViewY = 0;                       //move user's position
		}
	}
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP)
		bViewX = 0, bViewY = 0;                         //click other location
}
int main(int argc, char* argv[])
{
	void timer(int);
	glutInit(&argc, (char**)argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("hw2");
	glutDisplayFunc(display);
	glutTimerFunc(delay, timer, 0);
	glutMouseFunc(mouse_handler);             // add mouse handler
	glutKeyboardFunc(keyboard_handler);       // add keyboard handler
	glutMotionFunc(MyMouseMove);             // add mouse location funciton
	init();
	glutMainLoop();
}
void timer(int t) {
	glutPostRedisplay();
	glutTimerFunc(delay, timer, t);
}