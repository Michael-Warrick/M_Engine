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

    // Globally Accessible Variables
    GLFWwindow* window = nullptr;

    // Vertex Buffer Object + Vertex Array Object
    GLuint vertexBufferObject;
    GLuint vertexArrayObject;

    // Color Buffer Object
    GLuint colorBuffer;
};