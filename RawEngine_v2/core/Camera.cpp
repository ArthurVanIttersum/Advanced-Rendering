#include "Camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
namespace core
{
    Camera::Camera(glm::vec2 setScreenSize)
    {
        printf_s("making camera\n");
        //basic transform stuff
        position = glm::vec3(0.0f, 0.0f, 10.0f);
        heading = -90;
        pitch = 0;
        
        //projection matrix stuff
        cameraLength = 45.0f;
        fov = 45.0f;
        screenSize = setScreenSize;

        //update matrices and vectors
        UpdateVectors();
    }

    void Camera::UpdateVectors()
    {
        forwardDir = glm::vec3(0, sin(glm::radians(pitch)), 0) + cos(glm::radians(pitch)) * glm::vec3(cos(glm::radians(heading)), 0, sin(glm::radians(heading)));
        rightDir = glm::normalize(glm::cross(WorldUp, forwardDir));
        upDir = glm::cross(forwardDir, rightDir);
        viewMatrix = glm::lookAt(position, position + forwardDir * cameraLength, WorldUp);
        projectionMatrix = glm::perspective(glm::radians(fov), static_cast<float>(screenSize.x) / static_cast<float>(screenSize.y), 0.1f, 100.0f);
    }

    void Camera::Move(glm::vec3 offset, float deltaTime)
    {
        position += glm::vec3(offset.x * deltaTime, offset.y * deltaTime, offset.z * deltaTime);
        UpdateVectors();
    }

    void Camera::FOV(float enlargement)
    {
        fov += enlargement;
    }

    void Camera::UpdateScreenSize(glm::vec2 screenSize)
    {
        this->screenSize = screenSize;
        UpdateVectors();
    }

    void Camera::HandleInput(GLFWwindow* window, float deltaTime)
    {
        double oldPosX = mousePosX;
        double oldPosY = mousePosY;
        glfwGetCursorPos(window, &mousePosX, &mousePosY);
        float diffX = mousePosX - oldPosX;
        float diffY = mousePosY - oldPosY;

        if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS)
        {
            if (diffX != 0)
            {
                //printf_s("mouse is moving %f %f \n", diffX, diffY);
                heading += diffX * deltaTime * 100;
                UpdateVectors();
            }
            if (diffY != 0)
            {
                //printf_s("mouse is moving %f %f \n", diffX, diffY);
                pitch -= diffY * deltaTime * 100;
                UpdateVectors();
            }
        }
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            Move(forwardDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            Move(-forwardDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            Move(rightDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            Move(-rightDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        {
            Move(upDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        {
            Move(-upDir, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        {
            FOV(deltaTime * 2);
        }
        if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
        {
            FOV(-deltaTime * 2);
        }
        
    }
}