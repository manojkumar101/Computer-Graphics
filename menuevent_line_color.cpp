#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>
#include<iostream>
#include<math.h>
#define RED 1
#define BLUE 2
#define GREEN 3
#define WHITE 4

using namespace std;

GLint k=0,l=0,m=0,x2=0,y2=0,count=0,count1=0;
GLfloat red=1.0,green=1.0,blue=1.0;


void myInit(void)
{
	glClearColor(0.6,0.6,0.6,0.0);
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-400.0,400.0,-300.0,300.0);
}

void processMenuEvents(GLint option)
{
  switch(option)
  {
  case RED : red=1.0; blue=0.0; green=0.0; break;
  case BLUE : red=0.0; blue=1.0; green=0.0; break;
  case GREEN : red=0.0; blue=0.0; green=1.0; break;
  case WHITE : red=1.0; blue=1.0; green=1.0; break;
  }
  glColor3f(red,green,blue);


}


void myMoveMouse(GLint x,GLint y)
{
     if(count==0)
     {
    	 x2=x-400;
    	 y2=300-y;
    	 count++;
     }
     else
     {

	glBegin(GL_LINES);
	  glVertex2f(x2,y2);
	  glVertex2f(x-400,300-y);

    glEnd();
	 glFlush();
     x2=x-400,y2=300-y;
     }
   }

void myDisplay()
{


}

void myKeyboard(unsigned char thekey,GLint mx,GLint my)
{
	GLint x=mx-400;
	GLint y=300-my;
	switch(thekey)
	{
	case 'r':
		  k=1,l=0,m=0;
		  glColor3f(k,l,m);
		  break;
	case 'b':
		  k=0,l=0,m=1;
		  glColor3f(k,l,m);
		  break;
	case 'g':
		  k=0,l=1,m=0;
		  glColor3f(k,l,m);
		  break;
	default :
		break;

	}

}

void myMouse(int button,int state,int x,int y)
{

    if(state==GLUT_DOWN)
    {
    	if(button==GLUT_LEFT_BUTTON)
    	{	if(count==1)
    	    {k=1,l=1,m=1,count++;}
    	else
    	 	if(count==2)
    	    {k=1.5,l=1.5,m=1.5,count++;}
        	else
        	 	if(count==3)
        	    {k=0,l=0,m=0,count=0;}

    	  glColor3f(k,l,m);

    	}
    	else
    	{   glClear(GL_COLOR_BUFFER_BIT);
    		glClearColor(1.6,1.6,0.6,0.0);
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
	myInit();
	glutPassiveMotionFunc(myMoveMouse);
	glutMouseFunc(myMouse);
	glutKeyboardFunc(myKeyboard);
    glutCreateMenu(processMenuEvents);
     glutAddMenuEntry("red",RED);
     glutAddMenuEntry("blue",BLUE);
     glutAddMenuEntry("green",GREEN);
     glutAddMenuEntry("white",WHITE);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}
