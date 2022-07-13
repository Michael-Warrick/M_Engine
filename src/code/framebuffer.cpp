#include "../headers/framebuffer.hpp"

void Framebuffer::CreateBuffer() 
{
    glGenFramebuffers(1, &framebufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);

    glGenTextures(1, &colourTexture);
    glBindTexture(GL_TEXTURE_2D, colourTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colourTexture, 0);

    glGenRenderbuffers(1, &depthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, depthBuffer); 

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
    {
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::ClearBuffer() 
{
    glClearColor(0.45f, 0.76f, 0.98f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
}

void Framebuffer::BindBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebufferObject);
}

void Framebuffer::BindTexture(unsigned int texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
}

unsigned int Framebuffer::GetColourTexture()
{
    return colourTexture;
}

void Framebuffer::UnbindBuffer()
{
    glBindBuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::DeleteBuffer()
{
    glDeleteFramebuffers(GL_FRAMEBUFFER, &framebufferObject);
    glDeleteTextures(1, &colourTexture);
    glDeleteTextures(1, &depthTexture);
}