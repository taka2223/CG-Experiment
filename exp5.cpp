#include "loader.h"
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <string.h>
using namespace std;

// void setLightRes()
// {
//     GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
//     glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//     glEnable(GL_LIGHTING); //启用光源
//     glEnable(GL_LIGHT0); //使用指定灯光
// }
bool mouseDown = false;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;
void myinit()
{

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat white_light[] = { 0.0, 1.0, 1.0, 1.0 };
    GLfloat lmodel_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}
bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals)
{
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uvs;
    std::vector<glm::vec3> temp_normals;

    FILE* file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        return false;
    }

    while (1) {

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            cout << "Get v" << endl;
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            cout << "Get vt" << endl;
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            cout << "Get vn" << endl;
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            cout << "Get f" << endl;
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
            if (matches != 6) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        } else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }
    }

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        glm::vec3 vertex = temp_vertices[vertexIndex - 1];
        glm::vec3 normal = temp_normals[normalIndex - 1];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_normals.push_back(normal);
    }

    return true;
}
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseDown = true;
        xdiff = x - yrot;
        ydiff = -y + xrot;
        std::cout << "xdiff:" << xdiff << "\tydiff" << ydiff << std::endl;
    } else
        mouseDown = false;
}

// 鼠标移动事件
void mouseMotion(int x, int y)
{
    if (mouseDown) {
        yrot = x - xdiff;
        xrot = y + ydiff;
        std::cout << "yrot:" << yrot << "\txrot" << xrot << std::endl;

        glutPostRedisplay();
    }
}
vector<glm::vec3> vertices;
vector<glm::vec2> uvs;
vector<glm::vec3> normals;
void display()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glRotatef(xrot, 1.0f, 0.0f, 0.0f);
    glRotatef(yrot, 0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    for (auto ver : vertices) {
        glVertex3f(ver.x, ver.y, ver.z);
    }
    for (auto nor : normals) {
        glNormal3f(nor.x, nor.y, nor.z);
    }

    glEnd();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char** argv)
{
    bool res = loadOBJ("/home/zzx/code/CG/CG-Experiment/tables/1a8fe5baa2d4b5f7ee84261b3d20656/models/model_normalized.obj", vertices, uvs, normals);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Flag");
    myinit();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutMainLoop();

    return 0;
}