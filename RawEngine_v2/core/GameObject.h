#pragma once
#include <glad/glad.h>
#include <vector>
#include "material.h"
#include "model.h"


namespace core {

    class GameObject {
    public:
        //general data
        std::shared_ptr<Model> objectModel;
        std::shared_ptr<Material> objectMaterial;
        glm::mat4 modelMatrix;
        
        //methods
        GameObject(std::shared_ptr<core::Model> objectModel, std::shared_ptr<core::Material> objectMaterial);//basic
        
        void translate(glm::vec3 translation);
        void rotate(glm::vec3 axis, float radians);
        void scale(glm::vec3 scale);

        void DrawObject();
    };
}