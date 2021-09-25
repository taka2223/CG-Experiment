#include <GL/glut.h>
#include<iostream>
#include<math.h>
#include<ctime>
#include<cstdlib>
using namespace std;

double DDA[11];
double Brese[11];
    void myinit()
    {
        // attributes
        glClearColor(1.0,1.0,1.0,1.0);
        glColor3f(1.0f,0.0f,0.0f);
        // set up viewing
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluOrtho2D(0.0, 500.0,0.0,500.0);
        glMatrixMode(GL_MODELVIEW);
    }
    void lineDDA(int x0, int x1, int y0, int y1){
        if (x0>x1)
        {
            int t=x1;
            x1 = x0;
            x0 = t;
            t =y1;
            y1 = y0;
            y0 = t;

            /* x0 is less than x1 */
        }

        int dx = x1-x0, dy =y1-y0,step;
        float x_inc, y_inc,x=x0,y=y0;
        if (abs(dx)>abs(dy))
        {   
            step = dx;
            /* code */
        }
        else step=dy;
        float k =(float)dy/(float)dx;
        x_inc=(float)dx/step, y_inc = (float)dy/step;
        if (k<=-1)
        {   
            int t=x1;
            x1 = x0;
            x0 = t;
            t =y1;
            y1 = y0;
            y0 = t;
            /* code */
        }
        glPointSize(5);
        glBegin(GL_POINTS);
        for (size_t i = 0; i < abs(step); i++)
        {   
            glVertex2i(int(x+0.5),int(y+0.5));
            x+=x_inc;y+=y_inc;
            /* code */
        }
        glEnd();

    }
    void lineBrese(int x0, int x1, int y0, int y1){
        if (x0>x1)
        {
            int t=x1;
            x1 = x0;
            x0 = t;
            t =y1;
            y1 = y0;
            y0 = t;
            /* x0 is less than x1 */
        }
        int dx=abs(x1-x0),dy=abs(y1-y0);
        bool swap = false;
        if (dy>dx)
        {
            int temp = dx;
            dx = dy;
            dy = temp; 
            swap=true;
            /* k is larger than 1 */
        }
        int y_inc;
        if (y1-y0>0)
        {
            y_inc=1;
            /* code */
        }else y_inc=-1;
        
        
        int p = 2*dy-dx,x=x0,y=y0,two_dx=2*dx,two_dy=2*dy;
        glBegin(GL_POINTS);
        for (size_t i = 0; i <= dx; i++)
        {
            glVertex2i(x,y);
            if (p>0)
            {   
                if (!swap)
                {
                  y+=y_inc;  
                    /* code */
                }else x++;
                p-=two_dx;
                /* code */
            }
            if (!swap)
            {
                x++;
                /* code */
            }else y+=y_inc;
            p+=two_dy;
            
        }
        glEnd();
    }
    void display1()
    {

        glClear(GL_COLOR_BUFFER_BIT); 
        time_t beginDDA,endDDA, beginBrese,endBrese;
        double time0=0,time1=0;
        int count=5000;
        
        //5000 lines
        for (size_t i = 0; i < count; i++)
        {
            int x0=rand()%500,x1=rand()%500,y0=rand()%500,y1=rand()%500;
            beginDDA=clock();
            lineDDA(x0,x1,y0,y1);
            endDDA=clock();
            time0+=(double)(endDDA-beginDDA);

            beginBrese=clock();
            lineBrese(x0,x1,y0,y1);
            endBrese=clock();
            time1+=(double)(endBrese-beginBrese);
        }
        cout<<"timeDDA: "<<time0<<endl;
        cout<<"timeBrese: "<<time1<<endl;
        DDA[0]=time0;Brese[0]=time1;
        glClear(GL_COLOR_BUFFER_BIT);

        //10k,20k... 100k lines
        int num=10;
        for (size_t i = 1; i <=num; i++)
        {
            int count=i*10000;
            for (size_t k = 0; k <count ; k++)
            {
                int x0=rand()%500,x1=rand()%500,y0=rand()%500,y1=rand()%500;
                beginDDA=clock();
                lineDDA(x0,x1,y0,y1);
                endDDA=clock();
                time0+=(double)(endDDA-beginDDA)/CLOCKS_PER_SEC;

                beginBrese=clock();
                lineBrese(x0,x1,y0,y1);
                endBrese=clock();
                time1+=(double)(endBrese-beginBrese)/CLOCKS_PER_SEC;
            }
            DDA[i]=time0;Brese[i]=time1;
            cout<<"timeDDA: "<<time0<<endl;
            cout<<"timeBrese: "<<time1<<endl;
            glClear(GL_COLOR_BUFFER_BIT);
        }

        // linegraph
        
        glFlush();
    }
    double timeTran[6]={0.0};
    void display2(){
        int count=10000;
        time_t begin,end;
        int x0=0,x1=10,y0=0,y1=rand()%10;
        for (size_t i = 0; i < count; i++)
        {   
            begin=clock();
            lineDDA(x0,x1,y0,y1);
            end=clock();
            timeTran[0]+=(double)(end-begin)/CLOCKS_PER_SEC;
        }
        int k =1;
        for (size_t i = 1; i <=9; i+=2)
        {
            srand(786);
            x1 = i*100;
            for (size_t j = 0; j < count; j++)
            {
                y1=rand()%x1;
                begin=clock();
                lineDDA(x0,x1,y0,y1);
                end=clock();
                timeTran[k]+=(double)(end-begin)/CLOCKS_PER_SEC;
            }
            cout<<timeTran[k++]<<",";
        }
        glFlush(); 
    }
    int  main(int argc, char **argv)
    {   

        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
        glutInitWindowSize(500,500);
        glutInitWindowPosition(50,50);
        glutCreateWindow("Sierpinski Gasket");
        glutDisplayFunc(display2);
        myinit();
        glutMainLoop();
        return 0;
    }