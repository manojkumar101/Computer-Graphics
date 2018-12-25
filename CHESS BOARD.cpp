#include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;
GLint xx,yy,a,b,xx1,yy1,t,p,v;
GLfloat A[10][2],B[10][2],C[10][2],D[10][2],BB[2][2];
float rgb[3];
void myInit()
{  
   glClearColor(1,1,1,0.0);
   glClear(GL_COLOR_BUFFER_BIT);
   glColor3f(rgb[0],rgb[1],rgb[2]);
   glPointSize(1.0);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D(0.0,720.0,0.0,640.0);
   glFlush();
}


void setpixel(GLint x,GLint y)
{ glColor3f(rgb[0],rgb[1],rgb[2]);
  glPointSize(1.0);
  glBegin(GL_POINTS);
    glVertex2f(x,640-y);
  glEnd();
  glFlush();  
}


void getPixel(int x,int y,float *color)
{
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,color);
}


void dda(int x1,int y1,int x2,int y2)
{ 
  int i,j,k,dx,dy;
  float x,y;
  float xinc,yinc;
  dx=x2-x1;
  dy=y2-y1;
  if(abs(dx)>=abs(dy))
   k=abs(dx);
  else
   k=abs(dy);
  xinc=(float)dx/k;
  yinc=(float)dy/k;
  x=x1;
  y=y1;
  setpixel(x,y);
  for(i=0;i<abs(k);i++)
  { x=x+xinc;
    y=y+yinc;
    x1=x+0.5;
    y1=y+0.5;
    setpixel(x1,y1);
  }
}

void colorpp()
{ glColor3f(0.0f,0.0f,1.0f);
  glRecti(700,0,720,20);
  glColor3f(1.0f,0.0f,0.0f);
  glRecti(700,20,720,40);
  glColor3f(0.0f,1.0f,0.0f);
  glRecti(700,40,720,60);
  glFlush();

} 
void translate(GLfloat a[10][2],int x)
{ for(int i=0;i<10;i++)
   for(int j=0;j<2;j++)
     a[i][j]=a[i][j]+x;
}


void rotate(GLfloat a[10][2],GLfloat C[10][2])
{   float sum=0;
    for (int c = 0; c < 10; c++) {
      for (int d = 0; d < 2; d++) {
        for (int k = 0; k < 2; k++) {
          sum = sum + a[c][k]*BB[k][d];
        }
        C[c][d] = sum;
        sum = 0;
      }
    }
}

void initialise(GLfloat BB[2][2])
{  float angle=45*3.14/180;
   BB[0][0]=cos(angle);
   BB[0][1]=sin(angle);
   BB[1][1]=cos(angle);
   BB[1][0]=-sin(angle);
   //cout<<BB[0][0];
}

void floodfill(int x,int y)
    {
    	float color[3];
    	getPixel(x,640-y,color);
    	if(color[0] ==1 && color[1] ==1 && color[2] ==1  )
    	{
    		setpixel(x,y);
    		floodfill(x+1,y); 
    		floodfill(x,y+1);
    		floodfill(x-1,y);
    		floodfill(x,y-1);
    	}
    }
void mouse(int button,int state,int x,int y)
{  if(state==GLUT_DOWN)
    {    if(button==GLUT_MIDDLE_BUTTON)
         { colorpp();
           getPixel(x,640-y,rgb);
           glClearColor(1,1,1,0.0);
   	   glClear(GL_COLOR_BUFFER_BIT);
         }
        if(button==GLUT_LEFT_BUTTON)
	    { int i,j,k=0;
              glClearColor(1,1,1,0.0);
   	   	        glClear(GL_COLOR_BUFFER_BIT);
              for(i=0;i<5;i++)
              { A[i][0]=200+i*50;
                A[i][1]=200;
	   	        A[i+5][0]=200+i*50;
                A[i+5][1]=400;
              }
              for(i=0;i<5;i++)
              { B[i][1]=200+i*50;
                B[i][0]=200;
	   	        B[i+5][1]=200+i*50;
                B[i+5][0]=400;
              }
              for(i=0;i<5;i++)
              { dda(A[i][0],A[i][1],A[i+5][0],A[i+5][1]);
                dda(B[i][0],B[i][1],B[i+5][0],B[i+5][1]);
              }
             v=0;
 	    } 
         
              
       if(button==GLUT_RIGHT_BUTTON)
	    {      if(v==0){ 
                glClearColor(1,1,1,0.0);
   	   	        glClear(GL_COLOR_BUFFER_BIT);
                int X=300;
                translate(A,-X);
                translate(B,-X);
                initialise(BB);
                /*for(int i=0;i<2;i++)
                 { for(int j=0;j<2;j++)
                    cout<<BB[i][j]<<" ";
                   cout<<endl;
				 }*/
	        rotate(A,C);
		rotate(B,D);
				/*for(int i=0;i<10;i++)
                 { for(int j=0;j<2;j++)
                    cout<<C[i][j]<<" ";
                   cout<<endl;
				 }*/
		translate(C,+X);
                translate(D,+X);
		        for(int i=0;i<5;i++)
                { dda(C[i][0],C[i][1],C[i+5][0],C[i+5][1]);
                  dda(D[i][0],D[i][1],D[i+5][0],D[i+5][1]);
                }
               }
               if(v>1)
               { floodfill(x,y);
               }
               v++;
            }  
   } 
}

int main(int argc, char **argv)
{    	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
 	glutInitWindowSize(720.0,640.0);
	glutInitWindowPosition(100.0,100.0);
	glutCreateWindow("chess");
        myInit();
	//glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
        glutMainLoop();
}
