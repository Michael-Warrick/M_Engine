#include "definitions.hpp"

class Framebuffer
{
public:
    void CreateBuffer();
    void DeleteBuffer();
    void ClearBuffer();
    void BindBuffer();
    void BindTexture();
    void UnbindBuffer();
    GLuint GetColourTexture();
    
    GLuint framebufferObject;
    GLuint colourTexture;
    GLuint depthTexture;
    GLuint depthBuffer;
};
