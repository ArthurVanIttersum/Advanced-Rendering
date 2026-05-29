#pragma once

#include <vector>
#include <glm/ext/matrix_float4x4.hpp>
#include <GLFW/glfw3.h>
#include <vector>

namespace core {
    class Camera {
    public:
        // Core info:
        glm::vec3 position;
    private:
        float heading;
        float pitch;

        // deduced info: (cached)
    public: 
        glm::vec3 forwardDir;
    private:
        glm::vec3 rightDir;
        glm::vec3 upDir;


        const glm::vec3 WorldUp = glm::vec3(0, 1, 0);


        float cameraLength;
        float fov;
        glm::vec2 screenSize;

        double mousePosX = 0;
        double mousePosY = 0;
    public:
        glm::mat4 viewMatrix; //deduced
        glm::mat4 projectionMatrix;

        Camera(glm::vec2 screenSize);
        void Move(glm::vec3 offset, float deltaTime);
        
        void UpdateVectors();
        void FOV(float enlargement);
        void UpdateScreenSize(glm::vec2 screenSize);
        void HandleInput(GLFWwindow* window, float deltaTime);
    };
}