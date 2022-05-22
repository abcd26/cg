#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
#include <stdlib.h>
#include <cmath>

using namespace std;
#define screenheight 480
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
    glFlush();
}

void drawLine()
{
    float x=points[0][0], y=points[0][1];
    float del_x=points[1][0]-points[0][0];
    float del_y=points[1][1]-points[0][1];
    float m = del_y/del_x;
    float diff_x, diff_y;
    if(m<=1)
    {
        diff_x=1;
        diff_y=m;
    }
    else
    {
        diff_x=1/m;
        diff_y=1;
    }
    while(x != points[1][0])
    {
        glColor3d(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(x,y);
        glEnd();
        x += diff_x;
        y += diff_y;
    }
    glFlush();
}
static void mouse(int button, int status, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && status == GLUT_UP)
    {
        points.push_back({x,screenheight-y});
        if(points.size() == 2)
        {
            drawLine();
            points.clear();
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
    glutMouseFunc(mouse);

    glutMainLoop();

    return EXIT_SUCCESS;
}
