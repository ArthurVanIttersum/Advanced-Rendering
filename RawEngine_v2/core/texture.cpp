#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace core {
    Texture::Texture(const std::string &path)//load default
    {
        glGenTextures(1, &id);
        int width, height, nrComponents;
        if (unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0)) {
            GLenum format = 0;
            if (nrComponents == 1) {
                format = GL_RED;
            } else if (nrComponents == 3) {
                format = GL_RGB;
            } else if (nrComponents == 4) {
                format = GL_RGBA;
            }

            printf("Loaded with %d x %d [Components: %d]!\r\n", width, height, nrComponents);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0,
                         static_cast<GLint>(format)
                    , width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);
        } else {
            printf("Texture failed to load at path: %s\n", path.c_str());
            stbi_image_free(data);
        }
    }

    Texture::Texture(int width, int height)//simple default empty
    {
        
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture::Texture(const std::string& TMXPath, int isTileMap)//for tilemap
    {
        core::TilemapData map = core::TilemapLoader::loadTilemapFromTMX(TMXPath);

        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_R16UI, map.width, map.height, 0, GL_RED_INTEGER, GL_UNSIGNED_SHORT, map.tiles.data());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }

    Texture::Texture(const std::string& TSXpath, bool isTileSet)//load tileSet
    {

        core::TilesetData set = core::TilemapLoader::loadTilesetFromTSX(TSXpath);

        glGenTextures(1, &id);
        int width, height, nrComponents;
        if (unsigned char* data = stbi_load(set.imagePath.c_str(), &width, &height, &nrComponents, 0)) {
            GLenum format = 0;
            if (nrComponents == 1) {
                format = GL_RED;
            }
            else if (nrComponents == 3) {
                format = GL_RGB;
            }
            else if (nrComponents == 4) {
                format = GL_RGBA;
            }

            printf("Loaded with %d x %d [Components: %d]!\r\n", width, height, nrComponents);
            glBindTexture(GL_TEXTURE_2D, id);
            glTexImage2D(GL_TEXTURE_2D, 0,
                static_cast<GLint>(format)
                , width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

            glBindTexture(GL_TEXTURE_2D, 0);
            stbi_image_free(data);
        }
        else {
            printf("Texture failed to load at path: %s\n", set.imagePath.c_str());
            stbi_image_free(data);
        }
    }

    


    Texture::~Texture()
    {
        glDeleteTextures(1, &id);
    }

    void Texture::Resize(int width, int height)
    {
        glBindTexture(GL_TEXTURE_2D, id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    GLuint Texture::getId() {
        return id;
    }
}