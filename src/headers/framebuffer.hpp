#include "definitions.hpp"

class Framebuffer
{
public:
    void CreateBuffer();
    void DeleteBuffer();
    void ClearBuffer();
    void BindBuffer();
    void BindTexture(unsigned int texture);
    void UnbindBuffer();
    unsigned int GetColourTexture();
    
    unsigned int framebufferObject;
    unsigned int colourTexture;
    unsigned int depthTexture;
    unsigned int depthBuffer;
    
    int viewportWidth = 0;
    int viewportHeight = 0;
};
