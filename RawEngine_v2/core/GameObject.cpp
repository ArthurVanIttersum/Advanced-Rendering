#include "GameObject.h"

namespace core
{
    GameObject::GameObject(std::shared_ptr<core::Model> objectModel, std::shared_ptr<core::Material> objectMaterial)
    {
        printf_s("making gameobject\n");
        
        this->objectModel = objectModel;
        this->objectMaterial = objectMaterial;
        this->modelMatrix = glm::mat4(1.0f);
    }

    void GameObject::translate(glm::vec3 translation) {
        modelMatrix = glm::translate(modelMatrix, translation);
    }

    void GameObject::rotate(glm::vec3 axis, float radians) {
        modelMatrix = glm::rotate(modelMatrix, radians, axis);
    }

    void GameObject::scale(glm::vec3 scale) {
        modelMatrix = glm::scale(modelMatrix, scale);
    }

    void GameObject::DrawObject()
    {
        objectMaterial->SetupUniforms(modelMatrix);
        objectModel->render();
    }
}