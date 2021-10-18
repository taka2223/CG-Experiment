#include <GL/glut.h>
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

class loader {
private:
    vector<vector<GLfloat>> v; //vertexes
    vector<vector<vector<int>>> face; //surface
    vector<vector<GLfloat>> n; // normal
    vector<vector<GLfloat>> t;

public:
    loader(string);
    ~loader();
    void draw();
};

loader::loader(string filename)
{
    string line;
    ifstream f(filename);
    if (!f.is_open()) {
        cout << "open wrong" << endl;
    }
    int count = 1;
    while (getline(f, line)) {
        count++;
        vector<string> parameters;
        string tailMark = " ";
        string ans = "";

        line = line.append(tailMark);
        for (size_t i = 0; i < line.length(); i++) {
            char ch = line[i];
            if (ch != ' ') {
                ans += ch;
            } else {
                parameters.push_back(ans);
                ans = "";
            }
        }
        if (parameters[0] == "vn") {
            vector<GLfloat> vn;
            for (size_t i = 1; i < 4; i++) {
                float num = atof(parameters[i].c_str());
                vn.push_back(num);
                cout << "vn " << num << endl;
            }
            n.push_back(vn);
        } else if (parameters[0] == "vt") {
            vector<GLfloat> vt;
            for (size_t i = 1; i < 4; i++) {
                float num = atof(parameters[i].c_str());
                vt.push_back(num);
                cout << "vt " << num << endl;
            }
            t.push_back(vt);
        } else if (parameters[0] == "v") {
            vector<GLfloat> vertex;
            for (size_t i = 1; i < 4; i++) {
                float num = atof(parameters[i].c_str());
                vertex.push_back(num);
                cout << "vertex " << num << endl;
            }
            v.push_back(vertex);
        } else if (parameters[0] == "f") {
            vector<vector<int>> point;
            for (size_t i = 2; i < 5; i++) {
                vector<GLint> f_idx;
                string x = parameters[i];
                size_t pos = x.find_first_of('/');
                string a = x.substr(0, pos);
                size_t pos2 = x.find_first_of('/', pos + 1);
                f_idx.push_back(atoi(a.c_str()));
                string c = x.substr(pos2 + 1, x.length() - 1 - pos2);
                f_idx.push_back(atoi(c.c_str()));
                point.push_back(f_idx);
            }
            face.push_back(point);
        }
    }
    for (auto ver : v) {
        for (auto cor : ver) {
            cout << cor << " ";
        }
        cout << endl;
    }
    cout << "normal" << endl;
    for (auto ver : n) {
        for (auto cor : ver) {
            cout << cor << " ";
        }
        cout << endl;
    }
}

loader::~loader()
{
}

void loader::draw()
{
    cout << "face size: " << face.size() << endl;
    cout << "vertex.size: " << v.size() << endl;
    cout << "normal.size: " << n.size() << endl;
    glBegin(GL_TRIANGLES);
    cout << "draw" << endl;
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    // gluLookAt(4, 0, 1.5, 0, 0, 0, 1, 1, 0);
    glScalef(20, 20, 20);
    for (size_t i = 0; i < 1580; i++) {
        cout << "count :" << i << endl;
        // cout << n[face[i][0][1] - 1][0] << " " << n[face[i][0][1] - 1][1] << " " << n[face[i][0][1] - 1][2] << endl;
        glNormal3f(n[face[i][0][1] - 1][0], n[face[i][0][1] - 1][1], n[face[i][0][1] - 1][2]);
        glVertex3f(n[face[i][0][0] - 1][0], n[face[i][0][0] - 1][1], n[face[i][0][0] - 1][2]);
        glNormal3f(n[face[i][1][1] - 1][0], n[face[i][1][1] - 1][1], n[face[i][1][1] - 1][2]);
        glVertex3f(n[face[i][1][0] - 1][0], n[face[i][1][0] - 1][1], n[face[i][1][0] - 1][2]);
        glNormal3f(n[face[i][2][1] - 1][0], n[face[i][2][1] - 1][1], n[face[i][2][1] - 1][2]);
        // cout << "3n"
        //      << " ";
        glVertex3f(n[face[i][2][0] - 1][0], n[face[i][2][0] - 1][1], n[face[i][2][0] - 1][2]);
        // cout << "3v" << endl;
    }
    glEnd();
    glFlush();
}