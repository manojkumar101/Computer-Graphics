#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

vector<pair<float,float> > v;
int f;

void init2D()
{
	glClear(GL_COLOR_BUFFER_BIT);
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

void bresenhamLine(int x0,int y0,int x1,int y1)
{
	int dx=abs(x1-x0);
	int dy=abs(y1-y0);
	int x,y;
	if(dx>=dy)
	{
		int e=2*dy-dx;
		int inc1=2*dy;
		int inc2=2*(dy-dx);
		if(x0<x1)
			x=x0,y=y0;
		else 
			x=x1,y=y1,x1=x0,y1=y0;
		drawPixel(x,y);
		while(x<x1) 
		{
			if(e<0)
				e+=inc1;
			else 
			{
				if(y<y1)
					y++,e+=inc2;
				else
					y--,e+=inc2;
			}
			x++;
			drawPixel(x,y);
		}
	}
	else
	{
		int e=2*dx-dy;
		int inc1=2*dx;
		int inc2=2*(dx-dy);
		if(y0<y1)
			x=x0,y=y0;
		else
			x=x1,y=y1,y1=y0,x1=x0;
		drawPixel(x,y);
		while(y<y1)
		{
			if(e<0)
				e+=inc1;
			else
			{
				if(x>x1)
					x--,e+=inc2;
				else
					x++,e+=inc2;
			}
			y++;
			drawPixel(x,y);
		}
	}
}

void bresenhamCircle(int xCenter,int yCenter,int r)
{
	int x=0,y=r;
	int p=3/2-r;
	while(x<=y)
	{
		drawPixel(xCenter+x,yCenter+y);
		drawPixel(xCenter+y,yCenter+x);  
		drawPixel(xCenter-x,yCenter+y);
		drawPixel(xCenter+y,yCenter-x);
		drawPixel(xCenter-x,yCenter-y);
		drawPixel(xCenter-y,yCenter-x);
		drawPixel(xCenter+x,yCenter-y);
		drawPixel(xCenter-y,yCenter+x);
		if(p<0)
			p+=(2*x)+3;
		else
		{
			p+=(2*(x-y))+5;
			y-=1;
		}
		x++;
	}
}

void mouse(int button, int state, int xx, int yy)
{ 
    if(state== GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(f==1)
			{
				v.clear();
				f=0;
			}
			v.push_back(make_pair(xx,yy));
			drawPixel(xx,yy);
		}
		else if(button==GLUT_RIGHT_BUTTON)
		{
			for(int i=0;i<v.size()-1;i++)
 	        {
 	        	bresenhamLine(v[i].first,v[i].second,v[i+1].first,v[i+1].second);
 	        }
 	        int n=v.size();
 	        bresenhamLine(v[n-1].first,v[n-1].second,v[0].first,v[0].second);
 	        double a,b,c;
 	        double x1,y1,x2,y2,x3,y3;
 	        x1=v[0].first;y1=v[0].second;
 	        x2=v[1].first;y2=v[1].second;
 	        x3=v[2].first;y3=v[2].second;
 	        a=sqrt((x2-x3)*(x2-x3)+(y2-y3)*(y2-y3));
 	        b=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
 	        c=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
 	        int xx,yy;
 	        xx=(a*x1+b*x2+c*x3)/(a+b+c);
 	        yy=(a*y1+b*y2+c*y3)/(a+b+c);
 	        double area,peri=(a+b+c)/2;
 	        area=sqrt(peri*(peri-a)*(peri-b)*(peri-c));
 	        int radius=2*area/(a+b+c);
 	        bresenhamCircle(xx,yy,radius);
 	        double ad=x1*(y2-y3)-y1*(x2-x3)+(x2*y3)-(y2*x3);
 	        double bxd=(x1*x1+y1*y1)*(y2-y3)-y1*(x2*x2+y2*y2-(x3*x3+y3*y3))+(x2*x2+y2*y2)*y3-y2*(x3*x3+y3*y3);
 	        double byd=(x1*x1+y1*y1)*(x2-x3)-x1*(x2*x2+y2*y2-(x3*x3+y3*y3))+(x2*x2+y2*y2)*x3-x2*(x3*x3+y3*y3);
 	        double radius2=a*b*c/(4*area);
 	        bresenhamCircle(bxd/(2*ad),-byd/(2*ad),radius2);
 	        f=1;      
		}
	}
}

void keyboard(unsigned char ch,int x,int y)
{
	if (ch==27)
		exit (0);
}

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(0,0);
	glutCreateWindow("assign2");
	glutDisplayFunc(init2D);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
