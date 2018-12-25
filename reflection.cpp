#include<iostream>
using namespace std;
#include<Gl/gl.h>
#include<Gl/glu.h>
#include<Gl/glut.h>
#include<stdlib.h>
#include<math.h>
#define w 500
#define h 500

void setpixel(GLint x, GLint y)
{

	glColor3f(0.0,0.0,0.0);
	glPointSize(2.0);
	glBegin (GL_POINTS);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}
void setpixel1(GLfloat x, GLfloat y)
{

	glColor3f(0.0,0.0,1.0);
	glPointSize(2.0);
	glBegin (GL_POINTS);
		glVertex2f(x,y);
	glEnd();
	glFlush();
}
float mati[30][2],mato[30][2];
int k=0,c;
class reflection
{
      float ref[2][2];
      public:
      void mul(float s[2][2])
      {
            int i,j,k;
            float sum;
            for(i=0;i<c;i++)
            {
                for(j=0;j<2;j++)
                {
                    sum=0;
                    for(k=0;k<2;k++)
                        sum=sum+mati[i][k]*s[k][j];
                    mato[i][j]=sum;
                }
            }
      }
      void plot(float m[][2])
      {
           glColor3f(0,2,0);
           glBegin(GL_LINE_LOOP);
			for(int i=0;i<c;i++)
			        glVertex2f(m[i][0],m[i][1]);
            glEnd();
            glFlush();
      }
      void drawline(float m,float c1)
      {
           int i,j;
           float y;
           for(i=-250;i<250;i+=5)
           {
                                y=(m*i)+c1;
                                setpixel1(i,y);
           }
      }
      void refl_x()
      {
           ref[0][0]=1;
           ref[0][1]=0;
           ref[1][0]=0;
           ref[1][1]=-1;
           mul(ref);

      }
      void copy()
      {
           int i,j;
           for(i=0;i<c;i++)
           {
               for(j=0;j<2;j++)
               {
                   mati[i][j] = mato[i][j];
               }
           }
      }
      void refl_y()
      {
           ref[0][0]=-1;
           ref[0][1]=0;
           ref[1][0]=0;
           ref[1][1]=1;
           mul(ref);
           plot(mato);
      }
      void translation(float tx,float ty)
      {

           int i;

           for(i=0;i<c;i++)
           {
                           mato[i][0]=mati[i][0]+ tx;
                           mato[i][1]=mati[i][1]+ ty;
           }
      }

      void rotate(float angle)
      {
           int rot;
           float rota[2][2];
           rota[0][0]=cos(angle);
           rota[0][1]=-sin(angle);
           rota[1][0]=sin(angle);
           rota[1][1]=cos(angle);

           mul(rota);

      }
      void refl_arbit()
      {
           float m,c1,angle,y;
           int i,j;

           cout<<"\nEnter slope and y intercept of the line(y=m x +c)\n";
           cout<<"Enter slope (m)  :   ";
           cin>>m;
           cout<<"Enter y intercept (c) : ";
           cin>>c1;
           drawline(m,c1);
           translation(0,-c1);
           copy();
           angle=atan(m);
           rotate(angle);
           copy();
           refl_x();
           copy();
           rotate(-angle);
           copy();
           translation(0,c1);
           plot(mato);

      }
      void y_shear()
      {
           float a,y_sh[2][2];
           cout<<"\nEnter shearing constant (a) : ";
           cin>>a;
           y_sh[0][0]=1;
           y_sh[0][1]=a;
           y_sh[1][0]=0;
           y_sh[1][1]=1;
           mul(y_sh);
           plot(mato);
      }
      void x_shear()
      {
           float b,x_sh[2][2];
           cout<<"\nsEnter shearing constant (b) : ";
           cin>>b;
           x_sh[0][0]=1;
           x_sh[0][1]=0;
           x_sh[1][0]=b;
           x_sh[1][1]=1;
           mul(x_sh);
           plot(mato);
      }
};

void choice (void)
{
     int i,ch;
     glClear(GL_COLOR_BUFFER_BIT);
      glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(0.0,0.0,1.0);
	glPointSize(6.0);
	for(i=-w;i<=w;i++)
	{
		setpixel(i,0);
		setpixel(0,i);
	}
}
void init()
{
     glClearColor(1.0,1.0,1.0,1.0);
     glPointSize(4.0);
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluOrtho2D(-w/2,w/2,-h/2,h/2);

}

void keyboard (unsigned char key, int x, int y)
{
     if (key == 27)
        exit (0);
        else if(key =='r')
        {
            glBegin(GL_LINE_LOOP);
             for(int i=0;i<k;i++)
			  glVertex2f(mati[i][0],mati[i][1]);
			glEnd();
			c=k;
			k=0;
			glFlush();
        }
     else
         cout<<"You pressed :  %c\n"<<key;
}

void menu(int item)
{ /* Callback called when the user clicks the middle mouse button */
    reflection r;
    cout<<"\nMenu: you clicked item:\t" <<item;
    if(item==1)
    {
               r.refl_x();
               r.plot(mato);

    }
    if(item==2)
    {
                r.refl_y();
    }
    if(item==3)
    {
                r.refl_arbit();
    }
    if(item==4)
    {
                r.y_shear();
    }
    if(item==5)
    {
                r.x_shear();
    }
    if(item==6)
               exit(0);
}

void mouseClick(int button, int state, int x, int y)
{
    int x1,y1,p,q;

   if(state== GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			mati[k][0]=(float)(x-250);
			mati[k][1]=(float)(250-y);
			glColor3f(1,0,0);
			glBegin(GL_POINTS);
			glVertex2f(mati[k][0],mati[k][1]);
			glEnd();
			k++;
			glFlush();
		}
		if(button==GLUT_RIGHT_BUTTON)
		{
            glBegin(GL_LINE_LOOP);
             for(int i=0;i<k;i++)
			  glVertex2f(mati[i][0],mati[i][1]);
			glEnd();
			c=k;
			k=0;
			glFlush();
        }
	}
}
int main(int argc, char **argv)
{
    glutInit (&argc, argv); //initialise the device(glut window)
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(w,h);
    glutCreateWindow (" : Reflection :" );
    glutDisplayFunc (choice); //call backs are function pointers
    init();
    glutKeyboardFunc (keyboard);
    glutMouseFunc(mouseClick);
    glutCreateMenu (menu); //Create the first menu & add items
    glutAddMenuEntry ("About X axis", 1);
    glutAddMenuEntry ("About Y axis", 2);
    glutAddMenuEntry ("Arbitrary axis", 3);
    glutAddMenuEntry ("Y Shear",4);
    glutAddMenuEntry ("X Shear",5);
    glutAddMenuEntry ("Exit", 6);
    glutAttachMenu (GLUT_MIDDLE_BUTTON);//attach menu to middle button of mouse
    glutMainLoop();
    return 0;
}
