#include "ShaderProgram.h"

namespace core
{
    ShaderProgram::ShaderProgram(GLuint vs, GLuint fs)
    {
        printf_s("making ShaderProgram\n");
        int success;
        char infoLog[512];

        this->gLShaderProgram = glCreateProgram();
        glAttachShader(gLShaderProgram, vs);
        glAttachShader(gLShaderProgram, fs);
        glLinkProgram(gLShaderProgram);

        glGetProgramiv(gLShaderProgram, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(gLShaderProgram, 512, NULL, infoLog);
            printf("Error! Making Shader Program: %s\n", infoLog);
        }

    }
    ShaderProgram::~ShaderProgram()
    {
        printf_s("ShaderProgram deleted\n");
        glDeleteProgram(gLShaderProgram);
    }
}