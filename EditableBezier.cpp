#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define NO_POINTS 8

//Global Points for x and y coordinates
int x[100],y[100];
int q=0,k=0;

//For Drawing bezier between two calculated points
double oldX,oldY,currentX,currentY;

//Display Function that creates the scene and the worm
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glFlush();
}

//Factorial of a number
int fact(int x)
{
	if(x == 0)
		return 1;
	int facto=1;
	for(;x>0;x=x-1)
	{
		facto=facto*(x);
	}
	return facto;
}

//Initiate values for display
void init(void)
{
	glClearColor(0.529412, 0.807843, 0.921569, 0.0f); //Light blue color for background
	glColor3f(0.545098, 0.270588, 0.0745098); //Brown color for points
	glPointSize(10.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
 	gluOrtho2D(0,1280,0,720); //Set up orthographics matrix 
}

//Draw line between passed set of 2 points 
void drawLine(float l,float m, float j, float i)
{
	glBegin(GL_LINES);
	glVertex2f(l,m);
	glVertex2f(j,i);
	glEnd();
	glFlush();
}

//Drawing a point
void drawDot(int l, int m)
{
	glBegin(GL_POINTS);
	glVertex2i(l,m);
	glEnd();
	glFlush();
}

//Bernstein curve
void bern()
{
	double t;
	int i;
	for(t=0;t<=1.0;t=t+0.01)
	{
		currentX=0;
		currentY=0;
		for(i=0;i<=NO_POINTS;i++)
		{
			double Ci = (double)fact(NO_POINTS)/(double)(fact(NO_POINTS-i)*fact(i));
			double Cj = (double)(pow((1-t),NO_POINTS-i))*pow(t,i); 	
			currentX += Ci * Cj * x[i];
			currentY += Ci * Cj * y[i];
		}
		drawLine(oldX,720-oldY,currentX,720-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}

//Adjust curve everytime a point is moved
void editable(int i, int j)
{
	int d,z,k=0;
	for(d=0;d<=NO_POINTS;d++)
	{
		if((x[d]+5>i&&x[d]-5<i) && (y[d]+5>j&&y[d]-5<j))
		{
			x[d]=i;
			y[d]=j;
			d=100;
			glClear(GL_COLOR_BUFFER_BIT);
			oldX=x[0];
			oldY=y[0];
			bern();
			for(z=0;z<=NO_POINTS;z++)
				drawDot(x[z],720-y[z]);
		}
	}
}

//Draw points and creating a Bernstein curve	
void placeDots(int button, int state, int i, int j)
{
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(q<=NO_POINTS)
			{
				x[q]=(int)i;
				y[k]=(int)j;
				drawDot(x[q],720-y[k]);	
				if(q==0)oldX=x[q];
				if(q==0)oldY=y[q];
				q++;
				k++;
			}
			else if(q==NO_POINTS+1)
			{
				bern();
				q++;
				glutMouseFunc(NULL);
			}
			
		}	
	}
}	

//Function to intialize all values
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(0,0);
	glutCreateWindow("Bernstein Bezier");
	glutMouseFunc(placeDots);
	glutMotionFunc(editable);
 	glutDisplayFunc(display);
 	init();
	glutMainLoop();
	return 0;
} 
