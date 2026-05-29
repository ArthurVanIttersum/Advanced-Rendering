#pragma once

#include <glad/glad.h>
#include <string>
#include "TilemapLoader.h"

namespace core {

    class Texture {
    private:
        GLuint id;

    public:
        Texture(const std::string& path);
        Texture(int width, int height);
        Texture(const std::string& TMXPath, int isTileMap);
        Texture(const std::string& TSXpath, bool isTileSet);
        
        ~Texture();
        void Resize(int width, int height);

        GLuint getId();
    };

}
