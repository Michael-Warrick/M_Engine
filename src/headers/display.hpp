#include "definitions.hpp"

#include "shaderCompiler.hpp"
#include "camera.hpp"
#include "ui.hpp"

class Display
{
public:
    void Init();
    void PrepareFrame();
    void NextFrame();
    void Cleanup();

    GLFWwindow* window = nullptr;

    // macOS Retina Display fix
    // Also will help with higher res displays in general
    int retinaScreenWidth;
    int retinaScreenHeight;

    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
    unsigned int colorBuffer;
};