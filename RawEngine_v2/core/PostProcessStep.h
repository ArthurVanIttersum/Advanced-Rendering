#pragma once
#include <glad/glad.h>
#include <vector>
#include "material.h"
#include "model.h"


namespace core {

    class PostProcessStep {
    public:
        //general data
        std::shared_ptr<Model> objectModel;
        glm::mat4 modelMatrix;
        std::shared_ptr<core::ShaderProgram> shaderProgram;
        GLint textureModelUniform;
        GLint textureUniform;


        //methods
        PostProcessStep(std::shared_ptr<core::Model> objectModel, std::shared_ptr<core::ShaderProgram> shaderProgram);
        void DrawStep(std::shared_ptr<core::Texture> albedoTexture);

        
    };
}