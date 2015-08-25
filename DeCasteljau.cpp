#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#define NO_POINTS 4

//Global Points for x and y coordinates 
int x[NO_POINTS];
int y[NO_POINTS];
int q=0,k=0;

//For Drawing bezier between two calculated points
double oldX,oldY,currentX,currentY;

//Display Function
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);	
	glFlush();
}

//Initiate values for display
void init(void)
{
	glClearColor(0.529412, 0.807843, 0.921569, 0.0f);
	glColor3f(0.545098, 0.270588, 0.0745098);
	glPointSize(4.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Set up orthographics matrix
	gluOrtho2D(0,1280,0,720);
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

//De Casteljau's algorithm
void deCas()
{
	double t;
	for(t=0;t<=1.0;t=t+0.001)
	{
		currentX=(1-t)*((1-t)*((1-t)*x[0]+t*x[1])+t*((1-t)*x[1]+t*x[2]))+t*((1-t)*((1-t)*x[1]+t*x[2])+t*((1-t)*x[2]+t*x[3]));
		currentY=(1-t)*((1-t)*((1-t)*y[0]+t*y[1])+t*((1-t)*y[1]+t*y[2]))+t*((1-t)*((1-t)*y[1]+t*y[2])+t*((1-t)*y[2]+t*y[3]));
		drawLine(oldX,720-oldY,currentX,720-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}

//Draw points and curve using De Casteljau's 
void placeDots(int button, int state, int i, int j)
{
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(q < NO_POINTS)
			{
				x[q]=(int)i;
				y[k]=(int)j;
				drawDot(x[q],720-y[k]);	//Drawing the points clicked by mouse
				//For the first point in bezier
				if(q==0)oldX=x[q];	
				if(q==0)oldY=y[q];
				q++;
				k++;
			}
			else if(q == NO_POINTS)
			{
				deCas();
				q++;
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
	glutCreateWindow("De Casteljau's Algorithm");
	glutMouseFunc(placeDots);
 	glutDisplayFunc(display);
 	init();
	glutMainLoop();
	return 0;
}
 
