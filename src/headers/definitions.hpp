#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#if defined(_WIN64)
    #define PLATFORM_NAME "Windows 64-Bit"
#elif defined(__APPLE__) && defined(__MACH__)
    #define PLATFORM_NAME "macOS 64-Bit"
#elif defined(__linux__)
    #define PLATFORM_NAME "Linux 64-Bit"
#else
    #define PLATFORM_NAME "Unknown 64-bit OS"
#endif

#include <iostream>

#include "../UI/ImGui/imgui.h"
#include "../UI/ImGui/imgui_impl_glfw.h"
#include "../UI/ImGui/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM (OpenGL Maths library so that we don't have to write our own!)
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;
using namespace std;

#include <map>

#include <fstream>
#include <string>
#include <sstream>

#include <string.h>