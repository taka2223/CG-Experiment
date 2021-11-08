#include "loader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
using namespace std;

int genText()
{
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    int width, height, nrChannels;
    unsigned char* data = stbi_load("./图片1.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    return texture;
}

GLenum glCheckError_(const char* file, int line)
{
    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR) {
        std::string error;
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            error = "STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            error = "STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            error = "OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            error = "INVALID_FRAMEBUFFER_OPERATION";
            break;
        }
        std::cout << error << " | " << file << " (" << line << ")" << std::endl;
    }
    return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)
loader horses[117];
loader catuss[128];
void myinit()
{

    string suff = "./modelSequence/horses/horses_";
    string post = ".obj";
    string suff1 = "./modelSequence/cactus/cactus_";
    for (size_t i = 0; i < 117; i++) {
        string horse = suff + to_string(i) + post;
        loader temp(horse);
        horses[i] = temp;
    }
    for (size_t i = 0; i < 128; i++) {
        string catus = suff1 + to_string(i) + post;
        loader temp(catus);
        catuss[i] = temp;
    }

    glClearColor(1, 1, 1, 1);
    glEnable(GL_NORMALIZE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 800 / 600, 1.0, 21.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5, 6, 4, 0, 0, 0, 0, 1, 0);
    glColor3f(1.0f, 0.0f, 0.0f);
}

void display()
{
    // glEnable(GL_TEXTURE_2D);
    // cout << 111 << endl;
    // glClear(GL_COLOR_BUFFER_BIT);
    // cout << 222 << endl;
    // GLuint image = genText();
    // cout << 333 << endl;
    // glBindTexture(GL_TEXTURE_2D, image);
    // cout << 444 << endl;
    // glBegin(GL_POLYGON); //设置为多边形纹理贴图方式并开始贴图
    // // glTexCoord2f(0.0f, 0.0f);
    // glVertex2f(0, 0); //纹理左上角对应窗口左上角
    // cout << 555 << endl;
    // // glTexCoord2f(0.0f, 1.0f);
    // glVertex2f(0, 1); //纹理左下角对应窗口左下角
    // cout << 666 << endl;
    // // glTexCoord2f(1.0f, 1.0f);
    // glVertex2f(1, 1); //纹理右下角对应窗口右下角
    // cout << 777 << endl;
    // // glTexCoord2f(1.0f, 0.0f);
    // glVertex2f(0, 1); //纹理右上角对应窗口右上角
    // cout << "aaa";
    // glEnd(); //结束贴图
    // glutSwapBuffers();
    // glFlush();

    glColor3f(1.0, 0, 0);
    glPushMatrix();
    glScalef(3, 3, 3);
    int count = 20;
    while (count--) {
        for (size_t i = 0; i < 117; i++) {
            horses[i].draw();
            glutSwapBuffers();
            glClear(GL_COLOR_BUFFER_BIT);
            usleep(1000);
        }
    }
    glPopMatrix();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("sequence");
    myinit();
    glCheckError();
    glutDisplayFunc(display);
    glutMainLoop();
    glutMainLoop();
    glCheckError();
    return 0;
}