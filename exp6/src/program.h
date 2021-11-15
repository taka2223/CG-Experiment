#ifndef PROGRAM_H
#define PROGRAM_H

#include"shader.h"

class program
{
private:
    /* data */
public:
    unsigned int ID;
    void use();
    program(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~program();
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};

program::program(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    shader vertexShader(vertexPath);
    shader fragmentShader(fragmentPath);
    unsigned int vertex, fragment;
    vertex  = vertexShader.createVer();
    fragment = fragmentShader.createFra();

    ID = glCreateProgram();
    glAttachShader(ID,vertex);
    glAttachShader(ID,fragment);
    int success;
    char infoLog[512];
    glLinkProgram(ID);
    // 打印连接错误（如果有的话）
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
    }

    // 删除着色器，它们已经链接到我们的程序中了，已经不再需要了
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

program::~program()
{
}
void program::use() 
{ 
    glUseProgram(ID);
}
void program::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
}
void program::setInt(const std::string &name, int value) const
{ 
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}
void program::setFloat(const std::string &name, float value) const
{ 
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
} 
#endif