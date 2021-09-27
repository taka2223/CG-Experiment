#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;
void myinit()
{
    // attributes
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0f, 0.0f, 0.0f);
    // set up viewing
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500.0, 0.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
}
int N, M, count = 1;
int seq[5][6] = { 0 };
int dir[4][2] = {
    { 0, 1 },
    { 0, -1 },
    { 1, 0 },
    { -1, 0 }
};
void Number(int x0, int y0)
{
    if (x0 >= 0 && x0 <= 4 && y0 >= 0 && y0 <= 5) {
        if (seq[x0][y0] == 0) {

            seq[x0][y0] = count++;
            for (size_t i = 0; i < 4; i++) {
                int ran = rand() % 4;
                Number(x0 + dir[ran][0], y0 + dir[ran][1]);
            }
        }
    }
}

void erase()
{
    int x0 = rand() % 5;
    int y0 = rand() % 6;
    Number(x0, y0);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 6; j++) {
            cout << seq[i][j] << " ";
        }
        cout << endl;
    }

    glColor3f(0.0f, 0.0f, 0.0f);
    for (size_t i = 0; i < 5; i++) {
        for (size_t j = 0; j < 5; j++) {
            if (abs(seq[i][j] - seq[i][j + 1]) == 1) {
                cout << "draw:" << i << " , " << j << endl;
                glBegin(GL_LINES);
                glVertex2i((i + 1) * 70 + 1, j * 70 + 1);
                glVertex2i((i + 1) * 70 + 1, (j + 1) * 70 + 1);
                glEnd();
            }
        }
    }
    for (size_t i = 0; i < 6; i++) {
        for (size_t j = 0; j < 4; j++) {
            if (abs(seq[j][i] - seq[j + 1][i]) == 1) {
                cout << "draw:" << i << " , " << j << endl;
                glBegin(GL_LINES);
                glVertex2i(i * 70 + 1, (j + 1) * 70 + 1);
                glVertex2i((i + 1) * 70 + 1, (j + 1) * 70 + 1);
                glEnd();
            }
        }
    }
    glFlush();
}
void displaySG()
{
    glColor3f(1.0f, 0.0, 0.0);
    glBegin(GL_LINES);
    glLineWidth(2.0f);
    int x_ini = 1, y_ini = 1, temp_y = y_ini, temp_x = x_ini;
    for (size_t i = 0; i < N; i++) {
        /* draw the row */
        glVertex2i(x_ini, temp_y);
        glVertex2i(x_ini + 70 * M, temp_y);

        temp_y += 70;
    }
    for (size_t i = 0; i < M; i++) {
        /* column */
        glVertex2i(temp_x, y_ini);
        glVertex2i(temp_x, temp_y);
        temp_x += 70;
    }
    glVertex2i(x_ini, temp_y);
    glVertex2i(temp_x, temp_y);

    glVertex2i(temp_x, temp_y);
    glVertex2i(temp_x, y_ini);

    glEnd();
    erase();
    glFlush();
}
int main(int argc, char** argv)
{
    N = 5, M = 6;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Sierpinski Gasket");
    glutDisplayFunc(displaySG);
    myinit();
    glutMainLoop();
    return 0;
}