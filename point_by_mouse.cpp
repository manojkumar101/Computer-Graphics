#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
/*
 * pixel.cpp
 *
 *  Created on: Dec 31, 2013
 *      Author: it
 */

#include<iostream>
using namespace std;
void myInit(void)
{
	glClearColor(0.6,0.6,0.6,0.0);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0,400.0,-300.0,300.0);
}
void myDisplay(void)
{

	glFlush();
}

void myMouse(int button,int state,int x,int y)
{
  	GLint x1,y1;
    if(state==GLUT_DOWN)
    {
    	if(button==GLUT_LEFT_BUTTON)
    	{
    		glBegin(GL_POINTS);
    				glVertex2i(x-400,300-y);
    	    glEnd();
    		    glFlush();
    	}
    	else
    	{   glClear(GL_COLOR_BUFFER_BIT);
    		glClearColor(0.6,0.6,0.6,0.0);
    		glColor3f(1.0f,0.0f,0.0f);
    		glFlush();
    	}

    }

	return;
}
int main(int argc, char **argv)
{

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(800,600);
	glutInitWindowPosition(0,0);
	glutCreateWindow("My First Program");

	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	myInit();
	glutMainLoop();
	return 0;
}
