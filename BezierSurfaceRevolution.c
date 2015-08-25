//Creating a surface of revolution given a set of points 

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
#define pi 3.141592654
#define sample_t 0.1

int no_sample_pts = 1/sample_t + 1;
struct point 
{
	float x;
	float y;
}plot[1000];

struct point3D 
{
	float x;
	float y;
	float z;
}rot[1000];

struct vertex
{
	float vx;
	float vy;
	float vz;
};

struct edge
{
	struct vertex *first, *second;
};

struct face
{
	int p[4];
};

int no_of_pts = 0, n = 0;
int x[100], y[100];
int q=0, z=0, k=0, deg_rev = 0, f = 0;
float t=0; 
double oldX = 0, oldY = 0, currentX = 0, currentY = 0;

FILE *fp;

//Creating the surface of revolution and writing it in an OFF format
void rotate()
{
	struct vertex v[(deg_rev * no_sample_pts)];
	struct face fa[(deg_rev * (no_sample_pts - 1))];
	struct edge e[(deg_rev * (2*no_sample_pts - 1))];
	
	int i,j;	
	for(j=0;j < deg_rev;j++)
	{
		for(i=0; i < no_sample_pts;i++)
		{
			rot[i].x=plot[i].x * cos(j*(360/deg_rev)*(pi)/180);
			rot[i].y=plot[i].y;
			rot[i].z=plot[i].x * sin(j*(360/deg_rev)*(pi)/180);
		}
		
		for(i=0; i < no_sample_pts;i++)
		{
			v[j*no_sample_pts + i].vx=rot[i].x;
			v[j*no_sample_pts + i].vy=rot[i].y;
			v[j*no_sample_pts + i].vz=rot[i].z;
		}
	}
	
	for(i=0; i < (deg_rev-1)*no_sample_pts; i += no_sample_pts)
	{
		for(j = i; j < i + (no_sample_pts - 1); j++)
		{
			fa[f].p[0] = j;
			fa[f].p[1] = j + no_sample_pts;
			fa[f].p[2] = j + no_sample_pts + 1;
			fa[f].p[3] = j + 1;
			f++;
		}
	}
	
	for(i = (deg_rev - 1) * no_sample_pts; i < (deg_rev * no_sample_pts) - 1; i++)
	{
		fa[f].p[0] = i;
		fa[f].p[1] = i - (deg_rev-1) * no_sample_pts;
		fa[f].p[2] = i + 1 - (deg_rev-1) * no_sample_pts;
		fa[f].p[3] = i + 1;		
		f++;
	}
	
	fp=fopen("off_file.off","a");
	for(i=0; i < (deg_rev * no_sample_pts); i++)
	{
		fprintf(fp,"%f  %f  %f \n",v[i].vx,v[i].vy,v[i].vz);
	}

	fclose(fp);
	fp=fopen("off_file.off","a");
	for(i=0; i<(deg_rev*(no_sample_pts-1)); i++)
	{	
		fprintf(fp,"4 %d %d %d %d 1.000 0.000 0.000 1.000\n",fa[i].p[0],fa[i].p[1],fa[i].p[2],fa[i].p[3]);
	}
	fclose(fp);
}


//Display Function
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

//Factorial of a number
int fact(int x)
{
	if(x==0)return 1;
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

//Bernstein curve
void bern()
{
	double t;
	int i;
	for(t=0;t<=1.0;t=t + sample_t)
	{
		currentX=0;
		currentY=0;
		for(i=0;i<=no_of_pts;i++)
		{
			double Ci = (double)fact(no_of_pts)/(double)(fact(no_of_pts-i)*fact(i));
			double Cj = (double)(pow((1-t),no_of_pts-i))*pow(t,i); 	
			currentX += Ci * Cj * x[i];
			currentY += Ci * Cj * y[i];
		}
		plot[k].x = currentX;
		plot[k].y = currentY;
		k++;

		drawLine(oldX,720-oldY,currentX,720-currentY);
		oldX=currentX;
		oldY=currentY;
	}
}

//Draw points and creating a Bernstein curve		
void placeDots(int button, int state, int i, int j)
{
	if(state==GLUT_DOWN)
	{
		if(button==GLUT_LEFT_BUTTON)
		{
			if(q<=no_of_pts)
			{
				x[q]=(int)i;
				y[q]=(int)j;
				drawDot(x[q],720-y[q]);	
				if(q==0)oldX=x[q];
				if(q==0)oldY=y[q];
				q++;
			}
			else if(q==no_of_pts+1)
			{
				bern();
				for (i=0;i<no_sample_pts;i++)
					printf("%d %f    %f  \n",i,plot[i].x,plot[i].y);
				rotate();
				q++;
			}				
		}	
	}
}
	
//Function to intialize all values
int main(int argc,char **argv)
{
	int degree = 0;
	printf("\nEnter the degree of the curve: \t");
	scanf("%d", &degree);
	no_of_pts = degree - 1;
	printf("\nEnter the degree of the revolution: \t");
	scanf("%d", &deg_rev);
	deg_rev = (360/deg_rev);

	fp=fopen("off_file.off","w");
	fprintf(fp,"OFF\n%d %d %d\n",(deg_rev*no_sample_pts),(deg_rev*(no_sample_pts-1)),(deg_rev*(2*no_sample_pts-1)));
	fclose(fp);
	printf("\n\nSurface of revolution has been written into off_file.off. Use MeshLab or Geomview to view the file.");
	
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(1280,720);
	glutInitWindowPosition(0,0);
 	glutCreateWindow("Provide the sample curve");
	glutMouseFunc(placeDots);
 	glutDisplayFunc(display);
 	init();
	glutMainLoop();
	return 0;
} 
