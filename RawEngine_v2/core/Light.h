#pragma once

#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <GLFW/glfw3.h>


namespace core {

    enum LightType
    {
        direcitonalLight = 0,
        pointLight = 1
    };

    class Light {
    public:
        // Core info:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec4 color;
        LightType lightType;

    public:
        
        Light(glm::vec3 position, glm::vec3 direction, glm::vec4 color, LightType lightType);
        
        
    };
}