#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include "main.h"

using namespace std;

int Size = 600;
HINSTANCE h = LoadLibrary("laba_2.dll");
myVector rastVector;

// the reshape function
void reshape(GLsizei width, GLsizei height)
{
    glutReshapeWindow(Size,Size);
}

//draw the vertex
//if it exists
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (rastVector.canDraw())
    {
        vector <point> vectorToDraw = rastVector.getVector();
        for(int i = 0; i < vectorToDraw.size();i++)
        {
            glBegin(GL_POINTS);
            myColor colorOfPixel = vectorToDraw[i].getColor();
            point current = vectorToDraw[i];
            glColor3d(colorOfPixel.getR(),colorOfPixel.getG(),colorOfPixel.getB());
            glVertex2f(current.getX(),current.getY());
            glEnd();
        }
    }
    glFlush();

}

//creates points after the left button was pressed
void mouse(int button,int state,int x, int y)
{
    if (button == GLUT_LEFT_BUTTON)
    if (state == GLUT_DOWN)
    {
        if (rastVector.haveFirstPoint() == false)
        {
            point myFirst(x,Size - (double)y);
            float R = (rand()%10)/10.0;
            float G = (rand()%10)/10.0;
            float B = (rand()%10)/10.0;
            myColor color(R,G,B);
            myFirst.setColor(color);
            rastVector.putFirst(myFirst);
        }
        else
        {
            point mySecond(x,Size - (double)y);
            float R = (rand()%10)/10.0;
            float G = (rand()%10)/10.0;
            float B = (rand()%10)/10.0;
            myColor color(R,G,B);
            mySecond.setColor(color);
            rastVector.putLast(mySecond);
            display();
        }
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(Size, Size);
    glutInitWindowPosition(100,100);
    time(NULL);
    glutCreateWindow("Vector");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    float colorBase = 0.25;
    float opacity = 0.87;
    gluOrtho2D(0, Size, 0, Size);
    glClearColor(colorBase,colorBase,colorBase,opacity);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMainLoop();

}
