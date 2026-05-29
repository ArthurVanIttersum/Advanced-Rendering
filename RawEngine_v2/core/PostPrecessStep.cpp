#include "PostProcessStep.h"

namespace core
{
    PostProcessStep::PostProcessStep(std::shared_ptr<core::Model> objectModel, std::shared_ptr<core::ShaderProgram> shaderProgram)
    {
        printf_s("making PostProcessStep\n");

        this->objectModel = objectModel;
        this->shaderProgram = shaderProgram;
        this->modelMatrix = glm::mat4(1.0f);

        this->textureModelUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "mvpMatrix");
        this->textureUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "text");
    }

    void PostProcessStep::DrawStep(std::shared_ptr<core::Texture> InputTexture)
    {
        glUseProgram(shaderProgram->gLShaderProgram);
        glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(textureUniform, 0);
        glBindTexture(GL_TEXTURE_2D, InputTexture->getId());

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
        objectModel->render();
    }
}