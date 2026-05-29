#include "FrameBuffer.h"

namespace core
{
    FrameBuffer::FrameBuffer(int width, int height)
    {
        printf_s("making FrameBuffer\n");
        glGenFramebuffers(1, &frameBufferIdentifier);
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferIdentifier);

        this->colorBufferTexture = std::make_shared<core::Texture>(width, height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTexture->getId(), 0);

        glGenRenderbuffers(1, &renderBufferIdentifier);
        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferIdentifier);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferIdentifier);

        GLint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status == GL_FRAMEBUFFER_COMPLETE) {
            printf("Yay!\n");   // execute victory dance
        }
        else {
            printf("Sad... status: %d\n", status);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    FrameBuffer::~FrameBuffer()
    {
        glDeleteFramebuffers(1, &frameBufferIdentifier);
        glDeleteRenderbuffers(1, &renderBufferIdentifier);
    }

    void FrameBuffer::SetCurrentBuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferIdentifier);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void FrameBuffer::ResizeBuffer(int width, int height)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, frameBufferIdentifier);

        colorBufferTexture->Resize(static_cast<float>(width), static_cast<float>(height));
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorBufferTexture->getId(), 0);

        glBindRenderbuffer(GL_RENDERBUFFER, renderBufferIdentifier);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);
        
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBufferIdentifier);

        GLint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
        if (status == GL_FRAMEBUFFER_COMPLETE) {
            printf("Yay!\n");   // execute victory dance
        }
        else {
            printf("Sad... status: %d\n", status);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }


}