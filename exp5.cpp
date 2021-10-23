#include "loader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string.h>
using namespace std;

string chair = "/home/zzx/code/CG/CG-Experiment/chairs/2f1bc92c53f359d759a6208793b9dfca/models/model_normalized.obj";
string table = "/home/zzx/code/CG/CG-Experiment/tables/1a767b8130e8a5722a7d46e74f08da70/models/model_normalized.obj";
loader C(chair);
loader T(table);
void myinit()
{
    glClearColor(0, 0, 0, 0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800 / 600, 1.0, 21.0);
    // void gluPerspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFa)

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(6, 7, 8, 0, 0, 0, 0, 1, 0);
}
void room()
{
    glColor3f(1, 0, 0);
    glBegin(GL_LINES);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);

    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);

    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);

    // 3
    glVertex3f(-0.5, -0.5, -.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);

    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);

    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -.5);
    // 4
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);

    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);

    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);
    // 5
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, 0.5);

    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glEnd();
}

void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(0, -0.4, -1.0);
    glRotatef(180, 0, 1, 0);
    C.draw();
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(1.0, -0.4, -0.6);
    glRotatef(90, 0, 1, 0);
    C.draw();
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(1.0, -0.4, 0.6);
    glRotatef(90, 0, 1, 0);
    C.draw();
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(-1.0, -0.4, -0.6);
    glRotatef(-90, 0, 1, 0);
    C.draw();
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(-1.0, -0.4, 0.6);
    glRotatef(-90, 0, 1, 0);
    C.draw();
    glPopMatrix();

    glColor3f(0, 1, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(0.0, -0.4, 1.0);
    C.draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(3, 3, 3);
    glTranslatef(0, -0.4, 0.0);
    T.draw();
    glPopMatrix();

    glPushMatrix();
    glScalef(8, 8, 8);
    glTranslatef(0, 0.2, 0);
    room();
    glPopMatrix();

    glEnable(GL_NORMALIZE);
    glColor3f(1, 1, 1);

    glMatrixMode(GL_MODELVIEW);
    glEnd();
    glFlush();
}
vector<glm::vec3> c_vertices;
vector<glm::vec2> c_uvs;
vector<glm::vec3> c_normals;
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Room");
    myinit();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}