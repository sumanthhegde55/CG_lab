#include <GL/glut.h>
#include <iostream>
int id1,id2;
void draw(){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
	glColor3f(0,0,1);
	glVertex2i(100,100);
	glColor3f(0,1,1);
	glVertex2i(100,400);
	glColor3f(1,0,1);
	glVertex2i(400,400);
	glColor3f(1,1,0);
	glVertex2i(400,100);
	glEnd();
	glFlush();
	glutSwapBuffers();
}
void idle2(){
	glutSetWindow(id2);
	glTranslatef(250,250,0);
	glRotatef(.10,0,0,1);
	glTranslatef(-250,-250,0);
	glutPostRedisplay();
}
int main(int c,char**v){
	glutInit(&c,v);
	glutInitWindowSize(500,500);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
	id1=glutCreateWindow("1");
	glutDisplayFunc(draw);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,499,0,499);
	glClearColor(1,1,1,1);
	//glColor3i(1,0,0);
	id2=glutCreateWindow("2");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,499,0,499);
	glClearColor(1,1,1,1);
	glColor3i(1,0,0);
	glutDisplayFunc(draw);
	glutIdleFunc(idle2);
	glutMainLoop();
}
