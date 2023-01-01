#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;
typedef float vec2[2];

float m,it,t,xr,yr;

vec2 house[11] = {
	{100,100},
	{140,100},
	{140,150},
	{160,150},
	{160,100},
	{200,100},
	{200,200},
	{220,200},
	{150,300},
	{80,200},
	{100,200},
};
void drawhouse(){
	glBegin(GL_LINE_LOOP);
	for(auto v:house){
		glVertex2fv(v);
	}
	glEnd();
}
void drawusual(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0,1,0);drawhouse();glFlush();
}
void drawrefl(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	
	drawusual();
	
	glColor3f(0,0,1);
	int x0=0,x1=400;
	int y1 = m*x1+it,y0=m*x0+it;
	
	glBegin(GL_LINES);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
	glEnd();
	
	glPushMatrix();
	glTranslatef(0,it,0);
		float r = atan(m)*180/3.1415f;	
		glRotatef(r,0,0,1);
		glScalef(1,-1,1);
		glRotatef(-r,0,0,1);
	glTranslatef(0,-it,0);
	
	glColor3f(1,0,0);
	
	drawhouse();
	
	glPopMatrix();
	glFlush();
}
void drawrot(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	
	drawusual();
	
	glPushMatrix();
	
	glTranslatef(xr,yr,0);
	glRotatef(t,0,0,1);
	glTranslatef(-xr,-yr,0);
	
	glColor3f(1,0,0);
	drawhouse();
	glPopMatrix();
	glFlush();
}
int main(int c,char**v){
	glutInit(&c, v);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("House");
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,499,0,499);
	glClearColor(1,1,1,1);
	glMatrixMode(GL_MODELVIEW);
	int opt;
	cout<<"Input 1 for Reflection, 2 for Rotation\n";
	cin>>opt;
	if(opt==2){
		cout<<"t,xr,yr\n";
		cin>>t>>xr>>yr;
		glutDisplayFunc(drawrot);
	}
	if(opt==1){
		cout<<"m,c\n";
		cin>>m>>it;
		glutDisplayFunc(drawrefl);
	}
	glutMainLoop();
}
