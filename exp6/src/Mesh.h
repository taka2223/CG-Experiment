#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include "program.h"

using namespace std;

struct Vertex{
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
};

struct Texture
{
    unsigned int id;
    std::string type; 
};

class Mesh
{
private:
    unsigned int VAO,VBO,EBO;
    void setupMesh();
public:
    Mesh(vector<Vertex> vertices,vector<unsigned int> indices, vector<Texture> texures);
    ~Mesh();
    std::vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> texures;
    void Draw(program pro);
};

Mesh::Mesh(vector<Vertex> vertices,vector<unsigned int> indices, vector<Texture> texures)
{
    this->vertices = vertices;
    this->indices = indices;
    this->texures = texures;
    setupMesh();
}

Mesh::~Mesh()
{
}

