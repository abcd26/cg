#include <windows.h>
#include <bits/stdc++.h>
#include <cmath>
#include <GL/glut.h>
#include <stdlib.h>

#define screenheight 480
using namespace std;
vector< vector<float> > points;

static void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glBegin(GL_POLYGON);
        for(int k=0; k<points.size(); k++)
        {
            glVertex2f(points[k][0],points[k][1]);
        }
    glEnd();
    glFlush();
}

static void mouse(int button, int status, int x, int y)
{
    if(status == GLUT_UP && button == GLUT_LEFT_BUTTON)
    {
        points.push_back({x,screenheight-y});
    }
    glutPostRedisplay();
}

void translate(float tx, float ty)
{
    for(int k=0; k<points.size(); k++)
    {
        points[k][0] = points[k][0] + tx;
        points[k][1] = points[k][1] + ty;
    }
}

void rotation(float angle)
{
    float a=points[0][0], b=points[0][1];
    translate(-a,-b);
    for(int k=0; k<points.size(); k++)
    {
        float x=points[k][0], y=points[k][1];
        points[k][0] = x*cos(angle) - y*sin(angle);
        points[k][1] = x*sin(angle) + y*cos(angle);
    }
    translate(a,b);
}

void scaling(float sx, float sy)
{
    float a=points[0][0], b=points[0][1];
    translate(-a,-b);
    for(int k=0; k<points.size(); k++)
    {
        points[k][0] = points[k][0] * sx;
        points[k][1] = points[k][1] * sy;
    }
    translate(a,b);
}

void shearing(float shx)
{
    float a=points[0][0], b=points[0][1];
    translate(-a,-b);
    for(int k=0; k<points.size(); k++)
    {
        points[k][0] = points[k][0] + shx*points[k][1];
    }
    translate(a,b);
}

void shearingLine(float shx, float yref)
{
    float a=points[0][0], b=points[0][1];
    translate(-a,-b);
    for(int k=0; k<points.size(); k++)
    {
        points[k][0] = points[k][0] + shx*(points[k][1] - yref);
    }
    translate(a,b);
}
void reflect(unsigned char key)
{
    if(key == 'x')
    {
        translate(0,-240);
        for(int k=0; k<points.size(); k++)
        {
            points[k][1] = -points[k][1];
        }
        translate(0,240);
    }
    if(key == 'y')
    {
        translate(-320,0);
        for(int k=0; k<points.size(); k++)
        {
            points[k][0] = -points[k][0];
        }
        translate(320,0);
    }
}

void reflectLine(float m, float c)
{
    for(int k=0; k<points.size(); k++)
    {
        float x=points[k][0], y=points[k][1];
        points[k][0] = ((1-m*m)/(m*m+1))*x + ((2*m)/(m*m+1))*y - (2*c*m)/(m*m+1);
        points[k][1] = ((2*m)/(m*m+1))*x + ((m*m-1)/(m*m+1))*y + (2*c)/(m*m+1);
    }
}

void key(unsigned char key, int x, int y)
{
    switch(key)
    {
    case 't':
        translate(4,6);
        break;
    case 'r':
        rotation(2);
        break;
    case 's':
        scaling(1,2);
        break;
    case 'm':
        shearing(2);
        break;
    case 'n':
        shearingLine(2,-1);
        break;
    case 'x':
        reflect(key);
        break;
    case 'y':
        reflect(key);
        break;
    case 'z':
        reflectLine(1,0.5);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(key);

    glutMainLoop();

    return EXIT_SUCCESS;
}
