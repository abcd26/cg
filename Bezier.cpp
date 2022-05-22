#include<windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include<vector>
#include<math.h>
#include<iostream>
using namespace std;

vector<pair <float,float> > control_polygon;

static void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}

void plotpoint(int x,int y)
{
    glColor3d(1,0,0);
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}
void drawpolygon(vector< pair<float,float> > p)
{
    glBegin(GL_LINE_STRIP);
        glLineWidth(3);
        for(int i=0;i<p.size();i++)
            glVertex2f(p[i].first,p[i].second);
    glEnd();
    glFlush();
}
void bezier_curve(vector< pair<float,float> > p)
{
    vector< pair< float,float> > curve;
    float x, y;
    float start_t=0;
    float end_t=1;
    for(float t=start_t;t<=end_t;t=t+0.01)
    {
        x=pow(t,3)*p[0].first+ 3*t*t*(1-t)*p[1].first+3*t*(1-t)*(1-t)*p[2].first+ pow(1-t,3)*p[3].first;
        y=pow(t,3)*p[0].second+ 3*t*t*(1-t)*p[1].second+3*t*(1-t)*(1-t)*p[2].second+ pow(1-t,3)*p[3].second;
        pair<float,float> s(x,y);
        curve.push_back(s);
    }
    glColor3d(0,1,1);
    drawpolygon(curve);
}
static void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();

}
void mousehandler(int button,int status,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN)
    {
        pair<float,float> p;
        p.first=x;
        p.second=480-y;
        control_polygon.push_back(p);
        glColor3d(0,0,1);
        cout<<x<<y;
        plotpoint(x,480-y);
    }
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN)
    {
        glColor3d(1,0,0);
        //drawpolygon(control_polygon);
        bezier_curve(control_polygon);
        control_polygon.clear();

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

    glutMouseFunc(mousehandler);
    glutDisplayFunc(display);

    glClearColor(0,0,0,0);
    glutMainLoop();
    return EXIT_SUCCESS;
}

