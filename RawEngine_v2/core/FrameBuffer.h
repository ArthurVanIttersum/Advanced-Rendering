#pragma once
#include <glad/glad.h>
#include <vector>
#include "material.h"
#include "model.h"

namespace core {

    class FrameBuffer {
    public:
        //general data
        unsigned int frameBufferIdentifier;
        unsigned int renderBufferIdentifier;
        std::shared_ptr<core::Texture> colorBufferTexture;

        //methods
        FrameBuffer(int width, int height);
        ~FrameBuffer();
        void SetCurrentBuffer();
        void ResizeBuffer(int width, int height);

    };
}