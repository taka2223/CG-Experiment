#include "Mesh.h"


class Model
{
private:
    vector<Mesh> meshses;
    string directory;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);

    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
public:
    Model(char* path){
        loadModel(path);
    };
    ~Model();

    void Draw(program pro);
};

Model::Model(/* args */)
{
}

Model::~Model()
{
}

void Model::Draw(program pro){
    for (unsigned int  i = 0; i < meshses.size(); i++)
    {
        meshses[i].Draw(pro);
    }
}

void Model::loadModel(string path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path,aiProcess_Triangulate|aiProcess_FlipUVs);

    if (!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));

    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode *node,const aiScene* scene){
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshses.push_back(processMesh(mesh,scene));
    }

    for (unsigned int  i = 0; i < node->mChildren; i++)
    {
        processNode(node->mChildren[i],scene);
    }
        
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene){
    vector<Vertex> vertices;
    Vertex<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        
        vertices.push_back(Vertex);
    }
    // index

    //mat
    if (mesh->mMaterialIndex>=0)
    {
        /* code */
    }
    
    return Mesh(vertices,indices,textures);
    
}