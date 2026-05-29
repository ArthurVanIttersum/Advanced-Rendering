#include "material.h"

namespace core
{
    Material::Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera> mainCamera, std::shared_ptr<core::Light> light, int glossiness, float* ambientColor, float* ambientIntensity, glm::vec4 objectColor)//basic material
    {
        printf_s("making material\n");
        //this->albedoTexture = albedoTexture;
        this->shaderProgram = shaderProgram;
        this->materialType = lightMaterial;
        this->mainCamera = mainCamera;

        //special data
        mvpMatrixUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "mvpMatrix");
        modelMatrixUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "mMatrix");
        ambientColorUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "ambientColor");
        ambientIntensityUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "ambientIntensity");

        lightColorUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "lightColor");

        lightPositionUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "lightPosition");
        specularCamPosUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "specularCameraPosition");
        glossinessUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "glossiness");

        objectColorUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "objectColor");

        this->light = light;
        this->glossiness = glossiness;
        this->ambientColor = ambientColor;
        this->ambientIntensity = ambientIntensity;
        this->objectColor = objectColor;
    }

    Material::Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera> mainCamera, std::shared_ptr<core::Texture> albedoTexture)//texture material
    {
        printf_s("making material\n");
        this->shaderProgram = shaderProgram;
        this->materialType = textureMaterial;
        this->mainCamera = mainCamera;

        //special data
        this->albedoTexture = albedoTexture;

        textureModelUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "mvpMatrix");
        textureUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "text");

    }

    Material::Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera> mainCamera, std::shared_ptr<core::Texture> tileSetTexture, std::shared_ptr<core::Texture> tileMapTexture, const std::string& TSXpath)//tilemap material
    {
        printf_s("making material\n");
        this->shaderProgram = shaderProgram;
        this->materialType = tilemapMaterial;
        this->mainCamera = mainCamera;

        //special data
        tileSetTextureUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "tileSetTexture");
        tileSizeUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "tileSize");
        tileSetSizeUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "tileSetSize");
        tileMapTextureUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "tileMapTexture");
        this->tileSetTexture = tileSetTexture;
        this->tileMapTexture = tileMapTexture;

        textureModelUniform = glGetUniformLocation(shaderProgram->gLShaderProgram, "mvpMatrix");
        
        core::TilesetData set = core::TilemapLoader::loadTilesetFromTSX(TSXpath);

        this->tileWidth = set.tileWidth;
        this->tileHeight = set.tileHeight;
        this->tilesPerRow = set.tilesPerRow;
        this->tilesPerCol = set.tilesPerCol;
    }

    void Material::SetupUniforms(glm::mat4 modelMatrix)
    {
        if (materialType == lightMaterial)
        {
            glUseProgram(shaderProgram->gLShaderProgram);
            
            glUniform4f(ambientColorUniform, ambientColor[0], ambientColor[1], ambientColor[2], 1);//inMain
            glUniform1f(ambientIntensityUniform, *ambientIntensity);//inMain

            glUniform4f(lightColorUniform, light->color.r, light->color.g, light->color.b, light->color.a);
            glUniform3f(lightPositionUniform, light->position.x, light->position.y, light->position.z);

            glUniform3f(specularCamPosUniform, mainCamera->position.x, mainCamera->position.y, mainCamera->position.z);
            glUniform1f(glossinessUniform, glossiness);

            glUniformMatrix4fv(modelMatrixUniform, 1, GL_FALSE, glm::value_ptr(modelMatrix));

            glUniformMatrix4fv(mvpMatrixUniform, 1, GL_FALSE, glm::value_ptr(mainCamera->projectionMatrix * mainCamera->viewMatrix * modelMatrix));

            glUniform4f(objectColorUniform, objectColor.r, objectColor.g, objectColor.b, objectColor.a);
            
            glBindVertexArray(0);
            
        }
        if (materialType == textureMaterial)
        {
            glUseProgram(shaderProgram->gLShaderProgram);
            glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(mainCamera->projectionMatrix * mainCamera->viewMatrix * modelMatrix));
            glActiveTexture(GL_TEXTURE0);
            glUniform1i(textureUniform, 0);
            glBindTexture(GL_TEXTURE_2D, albedoTexture->getId());
            
            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);
        }
        if (materialType == tilemapMaterial)
        {


            glUseProgram(shaderProgram->gLShaderProgram);
            glUniformMatrix4fv(textureModelUniform, 1, GL_FALSE, glm::value_ptr(mainCamera->projectionMatrix * mainCamera->viewMatrix * modelMatrix));

            glActiveTexture(GL_TEXTURE0);
            glUniform1i(tileSetTextureUniform, 0);
            glBindTexture(GL_TEXTURE_2D, tileSetTexture->getId());

            glActiveTexture(GL_TEXTURE1);
            glUniform1i(tileMapTextureUniform, 1);
            glBindTexture(GL_TEXTURE_2D, tileMapTexture->getId());

            glUniform2i(tileSizeUniform, tileWidth, tileHeight);
            glUniform2i(tileSetSizeUniform, tilesPerRow, tilesPerCol);

            glBindVertexArray(0);
            glActiveTexture(GL_TEXTURE0);
        }
    }
}