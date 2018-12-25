#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include<iostream>
#include<math.h>


using namespace std;

GLint count=-1,x3,y3,x2,y2;
GLfloat r;


void myInit(void)
{
	glClearColor(0.6,0.6,0.6,0.0);
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0,400.0,-300.0,300.0);
}
void myDisplay()
{
	glPointSize(5.0);
	GLint x,y;
	GLfloat p;
	x=0,y=r;
	p=(5/4)-r;
	glBegin(GL_LINES);
	  glVertex2f(x3,y3);
	  glVertex2f(x2,y2);
    glEnd();
	 glFlush();

	while(x<=y)
	{
		glBegin(GL_POINTS);
    		glVertex2f(x3,y3);
		  glVertex2f(x3+x,y3+y);
		  glVertex2f(x3+y,y3+x);
		  glVertex2f(x3-x,y3+y);
		  glVertex2f(x3-y,y3+x);
		  glVertex2f(x3+x,y3-y);
		  glVertex2f(x3+y,y3-x);
		  glVertex2f(x3-x,y3-y);
		  glVertex2f(x3-y,y3-x);
		  glEnd();
		 glFlush();

		 if(p<0)
			 p=p+2*x+3;
		 else
		 {
			 p=p+2*x-2*y+5;
			 y--;
		 }
		 x++;
	}

    return;
}



void myMouse(int button,int state,int x,int y)
{
	GLfloat dx,dy;
    if(state==GLUT_DOWN)
    {
    	if(button==GLUT_LEFT_BUTTON)
    	{if(count==-1)
    	{
    		 glPointSize(2.0);
    		 glBegin(GL_LINES);
    		   glVertex2f(-400,0);
    		   glVertex2f(400,0);
    		   glVertex2f(0,-300);
    		   glVertex2f(0,300);
    		   glEnd();
            myDisplay();
    		count++;
    	}
    	else
    	  if(count==0)
           {
        	   x3=x-400;
        	   y3=300-y;
              count++;
           }
           else
            if(count==1)
            {
            	x2=x-400;
            	y2=300-y;
            	count++;
            }
           if(count==2)
           {
        	   dx=x2-x3;
        	   dy=y2-y3;
        	   dx=pow(dx,2);
        	   dy=pow(dy,2);
        	   dx=dx+dy;
        	   r=sqrt(dx);
        	   myDisplay();
        	   count=0;
           }
    	}
    	else
    	{   glClear(GL_COLOR_BUFFER_BIT);
    		glClearColor(0.6,0.6,0.6,0.0);
    		glColor3f(1.0f,0.0f,0.0f);
    		glFlush();
    		r=0;
    		count=-1;
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
