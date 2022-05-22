#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <iostream>
using namespace std;

vector <pair<int,int>> points;
int arrx[100], arry[100];

static void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void quadrant()
{
    //cout<<"Quadrant\n";
    glColor3d(1,1,1);
    glBegin(GL_LINES);
        glVertex2f(320,0);
        glVertex2f(320,480);
        glVertex2f(0,240);
        glVertex2f(640,240);
    glEnd();
    glFlush();
}

void drawPolygon()
{
    glBegin(GL_POLYGON);
        for(int i=0;i<points.size();i++)
        {
            glVertex2f(arrx[i],arry[i]);
        }
    glEnd();
    glFlush();
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);
    quadrant();
    drawPolygon();
}

void translate(int tx, int ty)
{
    for(int i=0;i<points.size();i++)
    {
        arrx[i] += tx;
        arry[i] += ty;
    }
}

void scale(float sx, float sy)
{
    int cx = arrx[0];
    int cy = arry[0];
    translate(-cx,-cy);
    for(int i=0;i<points.size();i++)
    {
        arrx[i] *= sx;
        arry[i] *= sy;
    }
    translate(cx,cy);
}

void rotation(float theta)
{
    int cx = arrx[0];
    int cy = arry[0];
    theta = theta*((2*3.14)/360.0);
    translate(-cx,-cy);

    for(int i=0;i<points.size();i++)
    {
        float x = arrx[i];
        float y = arry[i];
        arrx[i] = x*cos(theta) - y*sin(theta);
        arry[i] = x*sin(theta) + y*cos(theta);
    }
    translate(cx,cy);
}

void shearx(float shx,int yref)
{
    int cx = arrx[0];
    int cy = arry[0];
    translate(-cx,-cy);
    for(int i=0;i<points.size();i++)
    {
        arrx[i] += shx*(arry[i]-yref);
    }
    translate(cx,cy);
}
void sheary(float shy,int xref)
{
    int cx = arrx[0];
    int cy = arry[0];
    translate(-cx,-cy);
    for(int i=0;i<points.size();i++)
    {
        arry[i] += shy*(arrx[i]-xref);
    }
    translate(cx,cy);
}

void reflectx()
{
    for(int i=0;i<points.size();i++)
    {
        arry[i] = 480-arry[i];
    }
}

void reflecty()
{
    for(int i=0;i<points.size();i++)
    {
        arrx[i] = 640-arrx[i];
    }
}

void reflectmc(float m, float c)
{
    float x,y;
    for(int i=0;i<points.size();i++)
    {
        float x = arrx[i];
        float y = arry[i];
        arrx[i] = x*(1-m*m)/(m*m+1) + y*2*m/(m*m+1) - 2*m*c/(m*m+1);
        arry[i] = x*2*m/(m*m+1) + y*(m*m-1)/(m*m+1) + 2*c/(m*m+1);
    }
}

void keyHandler(unsigned char k, int x, int y)
{
    switch(k)
    {
        case 'w':
            translate(0,5);
            break;
        case 's':
            translate(0,-5);
            break;
        case 'd':
            translate(5,0);
            break;
        case 'a':
            translate(-5,0);
            break;
        case 'k':
            scale(2,2);
            break;
        case 'l':
            scale(0.5,0.5);
            break;
        case 'r':
            rotation(5);
            break;
        case 't':
            rotation(-5);
            break;
        case 'v':
            reflectx();
            break;
        case 'b':
            reflecty();
            break;
        case 'm':
            reflectmc(1,0);
            break;
        case 'x':
            shearx(0.25,0);
            break;
        case 'y':
            sheary(0.25,0);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void mouseHandler(int button, int status, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && status==GLUT_DOWN)
    {
        pair <int,int> p;
        p.first = x;
        p.second = 480-y;
        points.push_back(p);
    }
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN)
    {
        for(int i=0;i<points.size();i++)
        {
            arrx[i] = points[i].first;
            arry[i] = points[i].second;
        }
    }
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
    glutMouseFunc(mouseHandler);
    glutKeyboardFunc(keyHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}

