#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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