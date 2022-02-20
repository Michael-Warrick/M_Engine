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

    GLuint vertexBufferObject;
    GLuint vertexArrayObject;
    GLuint colorBuffer;

    GLuint frameBufferObject;
    GLuint frameBufferTexture;
    GLuint depthRenderObject;
};