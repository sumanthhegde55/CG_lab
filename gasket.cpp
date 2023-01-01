#include<iostream>
#include<GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>

typedef GLfloat point[3];

point tetra[4] = {{0,250,-250},{0,0,250},{250,-250,-250},{-250,-250,-250}};

int iter;

void draw_triangle(point p1,point p2,point p3){
	glVertex3fv(p1);
	glVertex3fv(p2);
	glVertex3fv(p3);
}

void draw_tetra(point p1,point p2,point p3,point p4){
	glColor3f(1,0,0);
	draw_triangle(p1,p2,p3);
	glColor3f(0,1,0);
	draw_triangle(p1,p3,p4);
	glColor3f(0,0,1);
	draw_triangle(p1,p4,p2);
	glColor3f(0,0,0);
	draw_triangle(p2,p3,p4);
}

void divide_tetra(point p1,point p2,point p3,point p4,int k){
	if(k > 0){
		point mid[6];
		
		for(int j=0;j<3;j++) mid[0][j] = (p1[j] + p2[j])/2;
		for(int j=0;j<3;j++) mid[1][j] = (p1[j] + p3[j])/2;
		for(int j=0;j<3;j++) mid[2][j] = (p1[j] + p4[j])/2;
		for(int j=0;j<3;j++) mid[3][j] = (p2[j] + p3[j])/2;
		for(int j=0;j<3;j++) mid[4][j] = (p2[j] + p4[j])/2;
		for(int j=0;j<3;j++) mid[5][j] = (p3[j] + p4[j])/2;
		
		divide_tetra(p1,mid[0],mid[1],mid[2],k-1);
		divide_tetra(mid[0],p2,mid[3],mid[4],k-1);
		divide_tetra(mid[1],mid[3],p3,mid[5],k-1);
		divide_tetra(mid[2],mid[4],p4,mid[5],k-1);
	}
	else{
		draw_tetra(p1,p2,p3,p4);
	}
}

void triangle(point a,point b,point c){
//point norm;
//cross(a,b,c,norm);
glBegin(GL_POLYGON);
glNormal3fv(a);
glVertex3fv(a);glVertex3fv(b);glVertex3fv(c);
glEnd();
}

void divide_triangle(point a,point b,point c,int k){
	point v1,v2,v3;
	if(k > 0){
	for(int j=0;j<3;j++) v1[j] = (a[j] + b[j])/2.0;
	for(int j=0;j<3;j++) v2[j] = (a[j] + c[j])/2.0;
	for(int j=0;j<3;j++) v3[j] = (b[j] + c[j])/2.0;
	divide_triangle(a,v1,v2,k-1);
	divide_triangle(c,v2,v3,k-1);
	divide_triangle(b,v3,v1,k-1);
	}
	else
		triangle(a,b,c);
}
void tetrahedron(int m){
	glColor3f(1,0,0);
	divide_triangle(tetra[0],tetra[1],tetra[2],m);
	glColor3f(0,1,0);
	divide_triangle(tetra[3],tetra[2],tetra[1],m);
	glColor3f(0,0,1);
	divide_triangle(tetra[0],tetra[3],tetra[1],m);
	glColor3f(0,0,0);
	divide_triangle(tetra[0],tetra[2],tetra[3],m);
}

void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	glBegin(GL_TRIANGLES);
	divide_tetra(tetra[0],tetra[1],tetra[2],tetra[3],iter);
	glEnd();
	*/
	tetrahedron(iter);
	glFlush();
}

void myinit(){
	glClearColor(1,1,1,1);
	glOrtho(-300,300,-300,300,-300,300);
}

int main(int argc,char **argv){
	std::cout << "enter no of iterations:";
	std::cin >> iter;
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("serpienski gasket");
	glutDisplayFunc(display);
	myinit();
	glEnable(GL_DEPTH_TEST);
	//glClearColor(1,1,1,1);
	glutMainLoop();
	return 0;
}
