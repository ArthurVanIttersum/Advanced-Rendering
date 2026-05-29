#pragma once
#include <glad/glad.h>
#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "texture.h"
#include "camera.h"
#include "model.h"
#include "Light.h"
#include "ShaderProgram.h"
#include <memory>
#include "TilemapLoader.h"

namespace core {

    enum MaterialType
    {
        lightMaterial = 0,
        textureMaterial = 1,
        tilemapMaterial = 2
    };

    class Material {
    public:
        //general data
        std::shared_ptr <ShaderProgram> shaderProgram;
        MaterialType materialType;
        
        std::shared_ptr<core::Camera> mainCamera;
        
        
        
        //basic material data
        GLint mvpMatrixUniform;
        GLint modelMatrixUniform;
        GLint ambientColorUniform;
        GLint ambientIntensityUniform;

        GLint lightColorUniform;
        GLint objectColorUniform;

        GLint diffuseColorUniform;
        GLint lightPositionUniform;
        GLint specularColorUniform;
        GLint specularCamPosUniform;
        GLint glossinessUniform;
        std::shared_ptr<core::Light> light;
        
        int glossiness;
        float* ambientColor;
        float* ambientIntensity;
        glm::vec4 objectColor;


        //texture material data
        GLint textureModelUniform;
        GLint textureUniform;
        std::shared_ptr<core::Texture> albedoTexture;
        
        //tilemap material data
        GLint tileSetTextureUniform;
        GLint tileSizeUniform;
        GLint tileSetSizeUniform;
        GLint tileMapTextureUniform;
        std::shared_ptr<core::Texture> tileSetTexture;
        std::shared_ptr<core::Texture> tileMapTexture;

        int tileWidth;
        int tileHeight;
        int tilesPerRow;
        int tilesPerCol;


        //methods
        Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera> mainCamera, std::shared_ptr<core::Light> light, int glosiness, float* ambientColor, float* ambientIntensity, glm::vec4 objectColor);//basic
        Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera>, std::shared_ptr<core::Texture> albedoTexture);//texture
        Material(std::shared_ptr<core::ShaderProgram> shaderProgram, std::shared_ptr<core::Camera>, std::shared_ptr<core::Texture> tileSetTexture, std::shared_ptr<core::Texture> tileMapTexture, const std::string& TSXpath);//tilemap
        void SetupUniforms(glm::mat4);
    };
}