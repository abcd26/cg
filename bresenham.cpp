#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>

using namespace std;

int cnt=1;
struct Point
{
    int x;
    int y;
}p[20];

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

int Sign(int n){
    if(n<0)
        return -1;
    else if(n>0)
        return 1;
    else
        return 0;
}

void set_pixel(int x, int y){
    glBegin(GL_POINTS);
        glVertex2f( x, y);
    glEnd();
}

static void drawLine(Point p1, Point p2){
    float x = p1.x;
    float y = p1.y;

    float del_y = abs(p2.y - y);
    float del_x = abs(p2.x - x);

    int s1 = Sign(p2.x - x);
    int s2 = Sign(p2.y - y);

    int interchange=0;
    if(del_y > del_x){

        float temp = del_x;
        del_x = del_y;
        del_y = temp;
        interchange = 1;
    }

    float p_k = 2*del_y - del_x;
    for(int i=1;i<=del_x;i++){
        set_pixel(x, y);
        cout<<x<<","<<y<<endl;
        while(p_k>0){
            if (interchange==1){
                x = x+s1;
            }
            else{
                y = y+s2;
            }
            p_k = p_k - 2*del_x;
        }
        if (interchange==1){
            y = y+s2;
        }
        else{
            x = x+s1;
        }
        p_k = p_k + 2*del_y;
    }
}

void mouseHandler(int button, int status, int x, int y)
{

    if(status==GLUT_UP && button==GLUT_LEFT_BUTTON)
    {
        p[cnt].x=x;
        p[cnt].y=480-y;
        glColor3d(1,0,0);
        glBegin(GL_POINTS);
            glVertex2f(p[cnt].x,p[cnt].y);
        glEnd();
        if(cnt == 2)
        {
            drawLine(p[cnt-1],p[cnt]);
            cnt = 0;
        }
        cnt++;
    }
    glFlush();
}


/* Program entry point */

static void init(){

    glClearColor(1,1,1,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);

    glutCreateWindow("GLUT Shapes");
    init();


    glutDisplayFunc(display);
    glClearColor(0,0,0,0);
    glutMouseFunc(mouseHandler);
    glutMainLoop();

    return EXIT_SUCCESS;
}
