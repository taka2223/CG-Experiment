#include <GL/glut.h>
#include <iostream>
using namespace std;

    float X1=250.0,Y1=500.0,X2=500.0,Y2=0.0;
    void myinit()
    {
        // attributes
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3f(1.0,0.0,0.0);
        
        // set up viewing
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 50.0,0.0,50.0);
        glMatrixMode(GL_MODELVIEW);
    }

    void displaySG()
    {
        GLfloat vertices[3][3] = {{0.0,0.0,0.0}, {250.0, 500.0,0.0}, {500.0,0.0,0.0}};
        if ((Y1!=Y2||Y1!=0.0||Y2!=0.0)&&(X1!=X2||X1!=0.0||X2!=0.0))
        {
            vertices[1][0]=X1;
            vertices[1][1]=Y1;
            vertices[2][0]=X2;
            vertices[2][1]=Y2;
        }
        else cout<<"3 vertexes are in the same line."<<endl;
        // an arbitrary triangle in the plane z = 0;
        GLfloat p[3] = {7.5, 5.0, 0.0};
                    // or set any desired initial point which is inside the triangle;
        int  j,k;
        int total_points = 50000;
        glBegin(GL_POINTS);
        for (k = 0; k < total_points; k++)
        {
                    /* pick a random vertex from 0, 1, 2*/
                    j = rand()%3;
                    // compute new location;
            p[0] = (p[0]+vertices[j][0])/2;
            p[1] = (p[1]+vertices[j][1])/2;
                    // display new point
                        glVertex3fv(p);
        }
        glEnd();
        glFlush();
    }
    int  main(int argc, char **argv)
    {   
        cout<<"Please input the coordinates of the two vertexs: "<<endl;
        cin>>X1>>Y1>>X2>>Y2;
            
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(50,50);
        glutCreateWindow("Sierpinski Gasket");
        glutDisplayFunc(displaySG);
        myinit();
        glutMainLoop();
        return 0;
    }