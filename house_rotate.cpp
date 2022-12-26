#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glut.h>

GLfloat house[3][9]={ {100.0,100.0,250.0,250.0,175.0,150.0,150.0,200.0,200.0},
	       	           {100.0,300.0,300.0,100.0,400.0,100.0,150.0,150.0,100.0},
	                         {1.0,   1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0,    1.0  }  };
GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat result[3][9]={{0},{0},{0}};
GLfloat h,k;
GLfloat theta,thetar;

void multiply()
{
	int i,j,l;
	for(i=0;i<3;i++)
	for(j=0;j<9;j++)
	     {
	       result[i][j]=0;
	       for(l=0;l<3;l++)
		result[i][j]=result[i][j]+rot_mat[i][l]*house[l][j];
	       }
}

void rotate()
{
	GLfloat m,n;
	m=h*(1-cos(thetar))+k*(sin(thetar));
	n=k*(1-cos(thetar))-h*(sin(thetar));
	rot_mat[0][0]=cos(thetar);
	rot_mat[0][1]=-sin(thetar);
	rot_mat[0][2]=m;
	rot_mat[1][0]=sin(thetar);
	rot_mat[1][1]=cos(thetar);
	rot_mat[1][2]=n;
	rot_mat[2][0]=0;
	rot_mat[2][1]=0;
	rot_mat[2][2]=1;
	multiply();
}

void draw_house()
{
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][0],house[1][0]);
	glVertex2f(house[0][1],house[1][1]);
	glVertex2f(house[0][2],house[1][2]);
	glVertex2f(house[0][3],house[1][3]);
	glEnd();
    glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][5],house[1][5]);
	glVertex2f(house[0][6],house[1][6]);
	glVertex2f(house[0][7],house[1][7]);
	glVertex2f(house[0][8],house[1][8]);
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(house[0][1],house[1][1]);
	glVertex2f(house[0][4],house[1][4]);
	glVertex2f(house[0][2],house[1][2]);
	glEnd();
}

void drawrotatedhouse()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][0],result[1][0]);
	glVertex2f(result[0][1],result[1][1]);
	glVertex2f(result[0][2],result[1][2]);
	glVertex2f(result[0][3],result[1][3]);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][5],result[1][5]);
	glVertex2f(result[0][6],result[1][6]);
	glVertex2f(result[0][7],result[1][7]);
	glVertex2f(result[0][8],result[1][8]);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(result[0][1],result[1][1]);
	glVertex2f(result[0][4],result[1][4]);
	glVertex2f(result[0][2],result[1][2]);
	glEnd();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	draw_house();
	rotate();	
	drawrotatedhouse();
	glFlush();
}

void myinit()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0);
	glLineWidth(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0,500.0,0.0,500.0);
}

int main(int argc,char *argv[])
{
	printf("enter the rotation angle\n");
	scanf("%f",&theta);
	printf("\nEnter the pivot point position\n");
	scanf("%f%f",&h,&k);
	thetar=theta*3.14/180;

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(0,0);
	glutCreateWindow("house rotation");
	glutDisplayFunc(display);
	myinit();
	glutMainLoop();
}