#include<windows.h>
#include<iostream>
#include<GL/glut.h>
#include<stdlib.h>
#include<vector>
#include<math.h>
#define SCREEN_HEIGHT 480
using namespace std;
vector< pair<float,float> > point;
vector< pair<float,float> > window;
vector< vector<int> > code;
static void init()
{
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,640,0,480);
}
void plotpoints(int x,int y)
{
    glBegin(GL_POINTS);
        glVertex2f(x,y);
    glEnd();
    glFlush();
}
void drawline()
{
    glBegin(GL_LINES);
        glVertex2f(point[0].first,point[0].second);
        glVertex2f(point[1].first,point[1].second);
    glEnd();
    glFlush();
}
void drawline(int x1,int y1,int x2,int y2)
{
    glColor3d(0,1,0);
    glBegin(GL_LINES);
        glVertex2f(x1,y1);
        glVertex2f(x2,y2);
    glEnd();
    glFlush();
}
void drawwindow()
{
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glBegin(GL_POLYGON);
        glVertex2f(window[0].first,window[0].second);
        glVertex2f(window[0].first,window[1].second);
        glVertex2f(window[1].first,window[1].second);
        glVertex2f(window[1].first,window[0].second);
    glEnd();
    glFlush();
}
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3d(1,0,0);
    glFlush();
}
void find_intersection(int i)
{
    float m=((point[1].second-point[0].second)/(point[1].first-point[0].first));
    float x,y;
    if(code[i][3]==1)
    {
        x=window[0].first;
        y=point[i].second+(m*(x-point[i].first));
        point[i].first=x;
        point[i].second=y;
    }
    if(code[i][0]==1)
    {
        y=window[1].second;
        x=point[i].first+((y-point[i].second)/m);
        point[i].first=x;
        point[i].second=y;
    }
    if(code[i][2]==1)
    {
        x=window[1].first;
        y=point[i].second+(m*(x-point[i].first));
        point[i].first=x;
        point[i].second=y;
    }
    if(code[i][1]==1)
    {
        y=window[0].second;
        x=point[i].first+((y-point[i].second)/m);
        point[i].first=x;
        point[i].second=y;
    }
}
void cohen_code()
{
    for(int i=0;i<2;i++)
    {
        int arr[]={0,0,0,0};
        if(point[i].second>window[1].second)
        {
            arr[0]=1;
        }
        if(point[i].second<window[0].second)
        {
            arr[1]=1;
        }
        if(point[i].first>window[1].first)
        {
            arr[2]=1;
        }
        if(point[i].first<window[0].first)
        {
            arr[3]=1;
        }
        vector<int> temp(arr,arr+4);
        code.push_back(temp);
    }
    int n[2]={0,0},k1=0;
    for(int k=0;k<code.size();k++)
    {
        int exp = 0;
        for(int j=code[k].size()-1;j>=0;j--)
        {
            n[k1] += code[k][j] * pow(2, exp);
            exp += 1;
        }
        k1+=1;
    }
    if((n[0] | n[1])==0)
    {
        cout<<"Trivial accept\n";
        drawline(point[0].first,point[0].second,point[1].first,point[1].second);
    }
    else if((n[0] & n[1])!=0)
    {
        cout<<"Trivial reject\n";
    }
    else
    {
        cout<<"Finding intersections...\n";
        find_intersection(0);
        find_intersection(1);
        drawline(point[0].first,point[0].second,point[1].first,point[1].second);
    }
}
static void mouse(int button,int status,int x,int y)
{
    if(button==GLUT_RIGHT_BUTTON && status==GLUT_DOWN)
    {
        pair<float,float> p;
        p.first=x;
        p.second=SCREEN_HEIGHT-y;
        plotpoints(p.first,p.second);
        window.push_back(p);
    }
    if(window.size()==2 && status==GLUT_DOWN)
    {
        drawwindow();
    }
    if(button==GLUT_LEFT_BUTTON && status==GLUT_DOWN)
    {
        pair<float,float> p;
        p.first=x;
        p.second=SCREEN_HEIGHT-y;
        plotpoints(p.first,p.second);
        point.push_back(p);
    }
    if(point.size()==2 && status==GLUT_DOWN)
    {
        drawline();
        cohen_code();
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
