#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

int height = 200, width = 300;
void myinit()
{
    // attributes
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);

    // set up viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}
void quad()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);
    glVertex3i(0, 0, 0);
    glVertex3i(300, 0, 0);
    glVertex3i(300, 200, 0);
    glVertex3i(0, 200, 0);
    glEnd();
}
void star()
{
    float r = height * 3 / 20, ax = r * cos(0.1 * M_PI), ay = r * sin(0.1 * M_PI);
    float bx = r * cos(0.3 * M_PI), by = r * sin(-0.3 * M_PI);
    float l = r * sin(0.1 * M_PI) / sin(0.3 * M_PI);
    float cx = l * cos(0.2 * M_PI), cy = l * sin(0.2 * M_PI);
    glColor3f(1.0, 1.0, 0.0);
    glPointSize(1);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, r, 0.0);
    glVertex3f(cx, ay, 0.0);
    glVertex3f(-cx, ay, 0.0);

    glVertex3f(-ax, ay, 0.0);
    glVertex3f(cx, ay, 0.0);
    glVertex3f(bx, by, 0.0);

    glVertex3f(ax, ay, 0.0);
    glVertex3f(-cx, cy, 0.0);
    glVertex3f(-bx, by, 0.0);
    glEnd();
    glFlush();
}
void displaySG()
{
    quad();
    glPushMatrix();
    glTranslatef(50.0, height * 0.75, 0.0);
    star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0, 180.0, 0.0);
    glScalef(0.33333, 0.33333, 0.3333);
    glRotatef(-36, 0.0, 0.0, 1.0);
    star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120.0, 160.0, 0.0);
    glScalef(0.33333, 0.33333, 0.3333);
    glRotatef(36, 0.0, 0.0, 1.0);
    star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(120.0, 130.0, 0.0);
    glScalef(0.33333, 0.33333, 0.3333);
    star();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(100.0, 110.0, 0.0);
    glScalef(0.33333, 0.33333, 0.3333);
    glRotatef(-36, 0.0, 0.0, 1.0);
    star();
    glPopMatrix();
    glFlush();
}
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Flag");
    glutDisplayFunc(displaySG);
    myinit();
    glutMainLoop();
    return 0;
}
