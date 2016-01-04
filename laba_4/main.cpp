#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include "shadow.h"

myClock clockScene;

//set color of drawing object
static void setColor(int color)
{
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, &materialColor[color][0]);
}

//draw the object
//it can be torus that have second radius to change in time
//or wire of icosahedron with static size
static void drawScene(int color)
{
    setColor(color);
    float radius = 0.09;
    glutSolidTorus(radius ,radius + 0.01 + clockScene.getClock() / 360.0,100,100);
   // if (tick > 0)glutWireIcosahedron();

}

//draw background of the scene
// it is needed to see object's shadow on it
//without background scene will consist only object and light
//background is a simple rectangle
void drawBackground(int Color)
{
    setColor(Color);
    int sizeGround = 4;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-sizeGround,-sizeGround,0);
    glVertex3f(sizeGround,-sizeGround,0);
    glVertex3f(sizeGround,sizeGround,0);
    glVertex3f(-sizeGround,sizeGround,0);
    glVertex3f(-sizeGround,-sizeGround,0);
    glEnd();
}
//create the shadow matrix of th object on scene
 void makeShadow(float ground[4], float light[4])
{
    float dot = 0.0;
    float shadow[4][4];
    for (int i = 0; i < 4; i++) dot += ground[i] * light[i];
    for (int i = 0; i< 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            shadow[i][j] = 0.0;
            if (i == j) shadow[i][j] += dot;
            shadow[i][j] -= light[j] * ground[i];
        }
    }
    glMultMatrixf((const GLfloat *) shadow);
}


// creates object which is changing during all the time
// and creates back plane on which we can see shadow  of the object from light
void display(void)
{
    GLfloat sceneForm[4][4];
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, -0.9);
    drawBackground(blue);
    glPopMatrix();
    glPushMatrix();
    glRotatef( clockScene.getClock() * 1.0 , 0, 0, 1);
    glScalef(1.0, 1.5, 1.0);
    glGetFloatv(GL_MODELVIEW_MATRIX, (GLfloat *) sceneForm);
    drawScene(red);
    glPopMatrix();
    glDepthMask(GL_FALSE);
    glEnable(GL_BLEND);
    glPushMatrix();
    glMultMatrixf((const GLfloat *) sceneForm);
    drawScene(black);
    glPopMatrix();
    glPushMatrix();
    makeShadow(backPlane, lightPos);
    glTranslatef(0.0, 0.0, 2.0);
    glMultMatrixf((const GLfloat *) sceneForm);
    drawScene(black);
    glPopMatrix();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
    glutSwapBuffers();
}


//this function creates picture which is changing
void timer(int = 0)
{
    clockScene.changeClock();
    display();
    glutTimerFunc(10,timer,0);
}

// make all initializations which are needed to create object on the scene and light and shadow
void initialization()
{
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      glFrustum(-1.0, 1.0, -1.0, 1.0, 1.0, 3.0);

      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      glTranslatef(0.0, 0.0, -2.0);

      glEnable(GL_DEPTH_TEST);
      glEnable(GL_LIGHTING);
      glEnable(GL_LIGHT0);
      glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
      glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
      glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiff);
      glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec);
      glEnable(GL_NORMALIZE);
      glEnable(GL_CULL_FACE);
      glCullFace(GL_BACK);
      glShadeModel(GL_SMOOTH);
      glClearColor(0.0, 0.0, 0.0, 1);
}


int main(int argc, char **argv)
{
    int windowSize = 500;
    char* name;
    name = "shadow";
    glutInitWindowSize(windowSize, windowSize);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutCreateWindow(name);
    initialization();
    glutDisplayFunc(display);
    timer();
    glutMainLoop();
    return 0;
}
