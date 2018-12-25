#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

#define w 500
#define h 500
#define max 50

int win[4][2],k=0,flag=0,m=0,n=0,flag1=0,wino[4][2],flag2=0;
int xmin,ymin,xmax,ymax;

void init()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(1.0,1.0,1.0,0.0);
	glPointSize(2.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-w/2,w/2,-h/2,h/2);
	glFlush();
}

class edge
{
public:
	int xc,yc;
};

edge e[max]; 
edge out[max]; 

void setpixel(GLint x, GLint y)
{      
	glColor3f(1.0,0.0,0.0);
	glPointSize(2.0);
	glBegin (GL_POINTS);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}

class clipping
{
public:   
	int left_below(int val,int min )
	{
		if(val>min)
			return 1;
		else 
			return 0; 
	}
	int right_above(int val,int min )
	{
		if(val>=min)
			return 0;
		else 
			return 1; 
	}
	void suth_hodge()
	{
		int k=0,j,i;
		float s;
		for(int index=0;index<4;index++)
		{
			if(index==0) //left Edge
			{
				for(j=0;j<m;j++)
				{
					if(!(left_below(e[j].xc,xmin)) && (left_below(e[j+1].xc,xmin))) //outside to inside with left edge
					{                                                        
						s=(float)(e[j+1].yc-e[j].yc)/(e[j+1].xc-e[j].xc);
						out[k].yc =e[j].yc+(int)(s*(xmin-e[j].xc));
						out[k].xc=xmin; 
						k++;
						out[k].yc =e[j+1].yc;
						out[k].xc =e[j+1].xc;
						k++;
					}
					else if((left_below(e[j].xc,xmin)) && !(left_below(e[j+1].xc,xmin))) //inside to outside  with left edge
					{
						s=(float)(e[j+1].yc-e[j].yc)/(e[j+1].xc-e[j].xc);
						out[k].yc =e[j].yc+(int)(s*(xmin-e[j].xc));
						out[k].xc=xmin;
						k++;
					}
					else if((left_below(e[j].xc,xmin)) && (left_below(e[j+1].xc,xmin))) //both are inside with left edge
					{
						out[k].yc =e[j+1].yc;
						out[k].xc =e[j+1].xc;
						k++;
					}
				}
				out[k].yc=out[0].yc;
				out[k].xc=out[0].xc;
				k++;
				m=k;
			}
			if(index==1) //right edge
			{
				k=0;
				for(j=0;j<m-1;j++)
				{
					if(!(left_below(out[j].yc,ymin)) && (left_below(out[j+1].yc,ymin))) //outside to inside with right edge
					{                                                          
						s=(float)(out[j+1].yc-out[j].yc)/(out[j+1].xc-out[j].xc);
						e[k].xc =out[j].xc+(int)((ymin-out[j].yc)/s);
						e[k].yc=ymin; 
						k++;
						e[k].yc=out[j+1].yc;
						e[k].xc=out[j+1].xc ;
						k++;
					}
					else if((left_below(out[j].yc,ymin)) && !(left_below(out[j+1].yc,ymin)))
					{
						s=(float)(out[j+1].yc-out[j].yc)/(out[j+1].xc-out[j].xc);
						e[k].xc =out[j].xc+(int)((ymin-out[j].yc)/s);
						e[k].yc=ymin; 
						k++;
					}
					else if((left_below(out[j].yc,ymin)) && (left_below(out[j+1].yc,ymin)))
					{
						e[k].yc=out[j+1].yc;
						e[k].xc=out[j+1].xc ;
						k++;
					}
				}
				e[k].yc=e[0].yc;
				e[k].xc=e[0].xc;
				k++;
				m=k;   
			}
			if(index==2)
			{
				k=0;
				for(j=0;j<m-1;j++)
				{
					if(!(right_above(e[j].xc,xmax)) && (right_above(e[j+1].xc,xmax)))
					{
						s=(float)(e[j+1].yc-e[j].yc)/(e[j+1].xc-e[j].xc);
						out[k].yc =e[j].yc+(int)(s*(xmax-e[j].xc));
						out[k].xc=xmax;
						k++;
						out[k].yc=e[j+1].yc;
						out[k].xc=e[j+1].xc ;
						k++;
					}
					if((right_above(e[j].xc,xmax)) && !(right_above(e[j+1].xc,xmax)))
					{
						s=(float)(e[j+1].yc-e[j].yc)/(e[j+1].xc-e[j].xc);
						out[k].yc =e[j].yc+(int)(s*(xmax-e[j].xc));
						out[k].xc=xmax;
						k++;
					}
					if((right_above(e[j].xc,xmax)) && (right_above(e[j+1].xc,xmax)))
					{
						out[k].yc=e[j+1].yc;
						out[k].xc=e[j+1].xc ;
						k++;
					}
				}
				out[k].yc=out[0].yc;
				out[k].xc=out[0].xc;
				k++;
				m=k;
			}
			if(index==3)
			{
				k=0;
				for(j=0;j<m-1;j++)
				{
					if(!(right_above(out[j].yc,ymax)) && (right_above(out[j+1].yc,ymax)))
					{
						s=(float)(out[j+1].yc-out[j].yc)/(out[j+1].xc-out[j].xc);
						e[k].xc = out[j].xc+(int)((ymax-out[j].yc)/s);
						e[k].yc=ymax;
						k++;
						e[k].yc=out[j+1].yc;
						e[k].xc=out[j+1].xc ;
						k++;
					}
					if((right_above(out[j].yc,ymax)) && !(right_above(out[j+1].yc,ymax)))
					{
						s=(float)(out[j+1].yc-out[j].yc)/(out[j+1].xc-out[j].xc);
						e[k].xc = out[j].xc+(int)((ymax-out[j].yc)/s);
						e[k].yc=ymax;
						k++;
					}
					if((right_above(out[j].yc,ymax)) && (right_above(out[j+1].yc,ymax)))
					{
						e[k].yc=out[j+1].yc;
						e[k].xc=out[j+1].xc ;
						k++;
					}
				}
				e[k].yc=e[0].yc;
				e[k].xc=e[0].xc;
				k++;
				m=k;  
			}
		}
	    glColor3f(0.0,1.0,0.0); 
		for(i=0;i<k-1;i++)
		{
			glBegin(GL_LINES);
			glVertex2i(e[i].xc,e[i].yc-250);
			glVertex2i(e[i+1].xc,e[i+1].yc-250);
			glEnd();
		}
		glFlush(); 
	} 
};

void max_min()
{
	if(win[0][0]<win[2][0])
	{
		xmin=win[0][0];
		xmax=win[2][0];
	}
	else
	{
		xmin=win[2][0];
		xmax=win[0][0];
	}
	if(win[0][1]<win[2][1])
	{
		ymin=win[0][1];
		ymax=win[2][1];
	}
	else
	{
		ymin=win[2][1];
		ymax=win[0][1];
	}   
}

void draw_window()
{
	win[1][0]=win[0][0];
	win[1][1]=win[2][1];
	win[3][0]=win[2][0];
	win[3][1]=win[0][1];
	glPointSize(4);
	glColor3f(0.0f,0.0f,1.0f);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<4;i++)
			glVertex2f(win[i][0],win[i][1]);
	glEnd();
	glFlush(); 
 }

void draw_winoutput()
{
	wino[0][0]=win[0][0];
	wino[1][0]=win[1][0];
	wino[2][0]=win[2][0];
	wino[3][0]=win[3][0];
	wino[0][1]=win[0][1]-250;
	wino[1][1]=win[1][1]-250;
	wino[2][1]=win[2][1]-250;
	wino[3][1]=win[3][1]-250;
	glColor3f(1.0f,0.0f,0.0f);
	glPointSize(4);
	glBegin(GL_LINE_LOOP);
		for(int i=0;i<4;i++)
			glVertex2f(wino[i][0],wino[i][1]);
	glEnd();
	glFlush();
} 

void mouse(int button, int state, int x, int y)
{
	clipping c;
	if(state== GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(flag==1)
			{
				e[m].xc=(x-250);
				e[m].yc=(250-y);
				glColor3f(1.0,0.0,0.0);
				glPointSize(4);
				glBegin(GL_POINTS);
				glVertex2f(e[m].xc,e[m].yc);              
				glEnd();
				if(m>0)
				{
					glBegin(GL_LINES);
					glVertex2f(e[m-1].xc,e[m-1].yc);              
					glVertex2f(e[m].xc,e[m].yc);
					glEnd();
				}
				m++;
				glFlush();
				flag1=1;
			}  
			else
			{         
				win[k][0]=(x-250);
				win[k][1]=(250-y);
				glColor3f(1,0,0);
				glBegin(GL_POINTS);
				glVertex2f(win[k][0],win[k][1]);
				glEnd();
				k=k+2;
				glFlush();
			}
		}
		if(button==GLUT_RIGHT_BUTTON)
		{
			flag=1;
			if(flag1==1)
			{
				glColor3f(1.0,0.0,0.0);
				glPointSize(4);       
				glBegin(GL_LINES);
					glVertex2f(e[m-1].xc,e[m-1].yc);
					glVertex2f(e[0].xc,e[0].yc);
				glEnd();
				e[m].yc=e[0].yc;
				e[m].xc=e[0].xc;
				glFlush();
				n++;
			}  
			else
			{                      
				max_min();
				draw_window();
			}
		} 
		else if(button==GLUT_MIDDLE_BUTTON)
		{
			draw_winoutput();
			c.suth_hodge();     
		}                  
	}  
}

void keyboard(unsigned char ch,int x,int y)
{
	if(ch==27)
		exit (0);
}

int main(int argc,char **argv)
{
    int choice;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(w,h);
    glutCreateWindow("assign5"); 
    glutDisplayFunc(init);
	glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}