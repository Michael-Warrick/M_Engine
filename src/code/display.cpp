#include "../headers/display.hpp"
#include "../headers/fpsCounter.h"

Camera cam;
ShaderCompiler shader;
UI ui;
FPS_Counter fpsCounter;

void MouseCallback(GLFWwindow* window, double xpos, double ypos);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void WindowResizeCallback(GLFWwindow* window, int width, int height);

bool isPaused = false;

void setOpenGLVersion(int majorContext, int minorContext) 
{
    // For Windows 10, 11... Set OpenGL version to 4.6 (latest).
    // For Mac OS, Set OpenGL to version 4.1 (latest version available for mac).
    // For Linux, Default to 3.3. Could go up to 4.5 in theory...
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorContext);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorContext);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

string setWindowTitle(string engineName) 
{
    std::string title = engineName + " - " + PLATFORM_NAME;
    return title;
}

void Display::Init()
{
    // MADE THIS RELATIVE WOOOOOO
    shader.LoadShaders("../shaders/cube.vert", "../shaders/cube.frag");
    
    glfwInit();
    setOpenGLVersion(4, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);     // Required for macOS, good for cross-platform dev
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    string title = setWindowTitle("M_Engine");
    const char* windowTitle = title.c_str();

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, windowTitle, nullptr, nullptr);

    // macOS Retina Display fix
    // Also will help with higher res displays in general
    int retinaScreenWidth;
    int retinaScreenHeight;
    glfwGetFramebufferSize(window, &retinaScreenWidth, &retinaScreenHeight);

    // Checks to see if our window hasn't been created and if not terminates GLFW
    if (nullptr == window)
    {
        std::cout << "Failed to create GLFW Window" << std::endl;
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);
    glfwSetWindowSizeCallback(window, WindowResizeCallback);
    glfwSetCursorPosCallback(window, MouseCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window, keyCallback);

    // 0 Disables V-SYNC, 1 Enables V-SYNC
    glfwSwapInterval(0);

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        std::cout << "Problem Initialising GLEW" << std::endl;
    }

    glViewport(0, 0, retinaScreenWidth, retinaScreenHeight);

    glClearColor(0.45f, 0.76f, 0.98f, 1.0f);

    glEnable(GL_BLEND | GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_CULL_FACE);

    shader.CompileShaders();

    // Generates our vertex arrays and buffers
    glGenVertexArrays(1, &vertexArrayObject);

    // Binding the vertexArrayObject + Setting vertex buffers
    glBindVertexArray(vertexArrayObject);

    // Our shape's vertices
    GLfloat vertices[] =
    {
        -1.0f,-1.0f,-1.0f, // triangle 1 : begin
        -1.0f,-1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, // triangle 1 : end
        1.0f, 1.0f,-1.0f, // triangle 2 : begin
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f, // triangle 2 : end
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        -1.0f,-1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f,-1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f,-1.0f,
        1.0f,-1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f,-1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f,-1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f,-1.0f, 1.0f
    };

    GLfloat colorData[] =
    {
        0.583f,  0.771f,  0.014f,
        0.609f,  0.115f,  0.436f,
        0.327f,  0.483f,  0.844f,
        0.822f,  0.569f,  0.201f,
        0.435f,  0.602f,  0.223f,
        0.310f,  0.747f,  0.185f,
        0.597f,  0.770f,  0.761f,
        0.559f,  0.436f,  0.730f,
        0.359f,  0.583f,  0.152f,
        0.483f,  0.596f,  0.789f,
        0.559f,  0.861f,  0.639f,
        0.195f,  0.548f,  0.859f,
        0.014f,  0.184f,  0.576f,
        0.771f,  0.328f,  0.970f,
        0.406f,  0.615f,  0.116f,
        0.676f,  0.977f,  0.133f,
        0.971f,  0.572f,  0.833f,
        0.140f,  0.616f,  0.489f,
        0.997f,  0.513f,  0.064f,
        0.945f,  0.719f,  0.592f,
        0.543f,  0.021f,  0.978f,
        0.279f,  0.317f,  0.505f,
        0.167f,  0.620f,  0.077f,
        0.347f,  0.857f,  0.137f,
        0.055f,  0.953f,  0.042f,
        0.714f,  0.505f,  0.345f,
        0.783f,  0.290f,  0.734f,
        0.722f,  0.645f,  0.174f,
        0.302f,  0.455f,  0.848f,
        0.225f,  0.587f,  0.040f,
        0.517f,  0.713f,  0.338f,
        0.053f,  0.959f,  0.120f,
        0.393f,  0.621f,  0.362f,
        0.673f,  0.211f,  0.457f,
        0.820f,  0.883f,  0.371f,
        0.982f,  0.099f,  0.879f
    };

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

    cam.CameraInit(shader.shaderProgram, window);

    ui.Init(window);
    fpsCounter.FPS_Counter_Init();
}

void Display::PrepareFrame()
{
    ui.Prepare();

    cam.CameraUpdate(window);

    if (!isPaused)
    {
        cam.ProcessKeyboardInput(window);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader.shaderProgram);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // Starts drawing a triangle at position[0] and with 3 vertices
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    ui.Render();
    fpsCounter.FPS_Counter_Update();
}

void Display::NextFrame()
{
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Display::Cleanup()
{
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &colorBuffer);
    glDeleteProgram(shader.shaderProgram);

    // Deallocating our vertex array
    glDeleteVertexArrays(1, &vertexArrayObject);

    ui.Destroy();
    fpsCounter.FPS_Counter_Destroy();

    glfwTerminate();
}

void MouseCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (cam.firstMouse)
    {
        cam.lastMouseX = xpos;
        cam.lastMouseY = ypos;

        cam.firstMouse = false;
    }

    double offsetX = xpos - cam.lastMouseX;
    double offsetY = cam.lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

    cam.lastMouseX = xpos;
    cam.lastMouseY = ypos;

    if (!isPaused)
    {
        cam.ProcessMouseMovement(offsetX, offsetY);
    }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        isPaused = !isPaused;

        // Pausing
        if (isPaused)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }

        // Resuming
        if (!isPaused)
        {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}

void WindowResizeCallback(GLFWwindow* window, int width, int height) 
{
    glViewport(0, 0, width, height);
}