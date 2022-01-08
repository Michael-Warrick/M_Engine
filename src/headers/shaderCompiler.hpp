#include "definitions.hpp"

using namespace std;

class ShaderCompiler {
public:

    void LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath);
    void CompileShaders();

    string vertexCode;
    string fragmentCode;

    GLuint shaderProgram;
};
