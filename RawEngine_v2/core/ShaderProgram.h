#pragma once
#include <glad/glad.h>
#include <vector>

namespace core {

    class ShaderProgram {
    public:
        //general data
        GLuint gLShaderProgram;

        //methods
        ShaderProgram(GLuint vs, GLuint fs);
        ~ShaderProgram();
    };
}