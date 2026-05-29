#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
namespace core
{
    Light::Light(glm::vec3 position, glm::vec3 direction, glm::vec4 color, LightType lightType)
    {
        printf_s("making light\n");
        //basic transorm stuff
        this->position = position;
        this->direction = direction;
        this->color = color;
        this->lightType = lightType;
        
    }

    
}