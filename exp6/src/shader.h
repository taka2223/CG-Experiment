#ifndef SHADER_H
#define SHADER_H

#include<glad/glad.h>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

class shader
{
private:
    std::string code;
public:
    shader(const GLchar* path);
    ~shader();
    const char* getCode();
    unsigned int createVer();
    unsigned int createFra();
};

shader::shader(const GLchar* path)
{
    std::ifstream shaderFile;
    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream<<shaderFile.rdbuf();
        shaderFile.close();
        code = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
}

shader::~shader()
{
}
const char* shader::getCode(){
    return code.c_str();
}
unsigned int shader::createVer(){
    unsigned int vertex;
    int success;
    char infoLog[512];
    std::cout<<code<<std::endl;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    const char* vShaderCode = getCode();
    glShaderSource(vertex,1,&vShaderCode,NULL);
    glCompileShader(vertex);
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }else
    {
        std::cout<<"SUCCESS!"<<std::endl;
    }
    return vertex;
}
unsigned int shader::createFra(){
    unsigned int fragment;
    int success;
    char infoLog[512];

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fShaderCode = getCode();
    glShaderSource(fragment,1,&fShaderCode,NULL);
    glCompileShader(fragment);
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragment, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
    }else
    {
        std::cout<<"SUCCESS!"<<std::endl;
    }
    return fragment;
}
#endif