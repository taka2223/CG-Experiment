#include <GL/glut.h>
#include <algorithm>
#include <fstream>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <iostream>
#include <math.h>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class loader {
private:
    vector<glm::vec2> text;
    vector<glm::vec3> vertex;
    vector<glm::vec3> normals;
    struct n_vertex {
        int v_index;
        int t_index = -1;
        int n_index = 1;
    };
    vector<vector<n_vertex>> faces;

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
        if (line.substr(0, 2) == "vt") {
            istringstream s(line.substr(2));
            glm::vec2 tex;
            s >> tex.x;
            s >> tex.y;
            tex.y = -tex.y;
            text.push_back(tex);
        } else if (line.substr(0, 2) == "vn") {
            istringstream s(line.substr(2));
            glm::vec3 norm;
            s >> norm.x;
            s >> norm.y;
            s >> norm.z;
            normals.push_back(norm);
        } else if (line.substr(0, 1) == "v") {
            istringstream s(line.substr(1));
            glm::vec3 ver;
            s >> ver.x;
            s >> ver.y;
            s >> ver.z;
            vertex.push_back(ver);
        } else if (line.substr(0, 1) == "f") {
            istringstream s(line.substr(1));
            string index;
            vector<n_vertex> face;
            while (s >> index) {
                n_vertex temp;
                replace(index.begin(), index.end(), '/', ' ');
                cout << index << endl;
                istringstream index_stream(index);
                if (index.find("  ") != string::npos) {
                    index_stream >> temp.v_index
                        >> temp.n_index;
                    temp.v_index--;
                    temp.n_index--;
                } else {
                    index_stream >> temp.v_index
                        >> temp.t_index
                        >> temp.n_index;

                    temp.v_index--;
                    temp.t_index--;
                    temp.n_index--;
                }
                face.push_back(temp);
            }
            faces.push_back(face);
        } else if (line[0] == '#') {
        } else {
        }
    }
}

loader::~loader()
{
}

void loader::draw()
{
    if (text.size() > 0) {
        for (size_t i = 0; i < faces.size(); i++) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            glBegin(GL_TRIANGLES);
            for (size_t j = 0; j < 3; j++) {
                int t_idx = faces[i][j].t_index;
                if (t_idx <= 0) {
                    continue;
                }
                glTexCoord2f(text[t_idx].x, text[t_idx].y);
                int n_idx = faces[i][j].n_index;
                glNormal3f(normals[n_idx].x, normals[n_idx].y, normals[n_idx].z);
                int v_idx = faces[i][j].v_index;
                glVertex3f(vertex[v_idx].x, vertex[v_idx].y, vertex[v_idx].z);
            }
            glEnd();
        }
    } else {
        for (size_t i = 0; i < faces.size(); i++) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            cout << "begin" << endl;
            glBegin(GL_TRIANGLES);
            for (size_t j = 0; j < 3; j++) {
                int n_idx = faces[i][j].n_index;
                glNormal3f(normals[n_idx].x, normals[n_idx].y, normals[n_idx].z);
                int v_idx = faces[i][j].v_index;
                glVertex3f(vertex[v_idx].x, vertex[v_idx].y, vertex[v_idx].z);
            }
            glEnd();
        }
    }
    cout << "draw end" << endl;
}