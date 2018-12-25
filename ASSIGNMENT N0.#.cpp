#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

double X1,Y1,X2,Y2;
vector<int> x_coordinates,y_coordinates;
int f,flag;

void init2D()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,640,0,480);
}

void drawPixel(int x,int y)
{
	glBegin(GL_POINTS);
		glVertex2i(x,480-y);
	glEnd();
	glFlush();
}

void dda(double x1,double y1,double x2,double y2)
{
	double dx=(x2-x1);
	double dy=(y2-y1);
	double len;
	float xInc,yInc,x=x1,y=y1;
	len=(abs(dx)>abs(dy))?(abs(dx)):(abs(dy));
	xInc=dx/(float)len;
	yInc=dy/(float)len;
	drawPixel(round(x),round(y));
	int k;
	for(k=0;k<len;k++)
	{
		x+=xInc;
		y+=yInc;
		drawPixel(round(x),round(y));
	}
}

void mouse(int button,int state,int x,int y)
{
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(flag==1)
			{
				x_coordinates.clear();
				y_coordinates.clear();
				flag=0,f=0;
			}
			if(f==0 && flag==0)
				X1=x,Y1=y,f=1;
			else
			{
				X2=x,Y2=y;
				double x1=X1,y1=Y1,x2=X1,y2=Y2,x3=X2,y3=Y2,x4=X2,y4=Y1;
				x_coordinates.push_back(x1),y_coordinates.push_back(y1);
				x_coordinates.push_back(x2),y_coordinates.push_back(y2);
				x_coordinates.push_back(x3),y_coordinates.push_back(y3);
				x_coordinates.push_back(x4),y_coordinates.push_back(y4);
				y1=(Y2-Y1)/2+Y1,x2=(X2-X1)/2+X1,y3=y1,x4=x2;
				x_coordinates.push_back(x1),y_coordinates.push_back(y1);
				x_coordinates.push_back(x2),y_coordinates.push_back(y2);
				x_coordinates.push_back(x3),y_coordinates.push_back(y3);
				x_coordinates.push_back(x4),y_coordinates.push_back(y4);
				x1=(x2+x1)/2,y1=(y2+y1)/2,x2=(x4+x3)/2,y2=y1,x3=x2,y3=(y4+y3)/2,x4=x1,y4=y3;
				x_coordinates.push_back(x1),y_coordinates.push_back(y1);
				x_coordinates.push_back(x2),y_coordinates.push_back(y2);
				x_coordinates.push_back(x3),y_coordinates.push_back(y3);
				x_coordinates.push_back(x4),y_coordinates.push_back(y4);
			}
			drawPixel(x,y);
		}
		else if(button==GLUT_RIGHT_BUTTON)
		{
			for(int i=0;i<x_coordinates.size();i++)
			{
				if((i+1)%4==0)
					dda(x_coordinates[i],y_coordinates[i],x_coordinates[i-3],y_coordinates[i-3]);
				else
					dda(x_coordinates[i],y_coordinates[i],x_coordinates[i+1],y_coordinates[i+1]);
			}
			flag=1;
		}
	}
}

void keyboard(unsigned char key,int x,int y)
{
	if(key==27)
		exit(0);
}

int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("assign3");
	glutDisplayFunc(init2D);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}