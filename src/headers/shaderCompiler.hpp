#include "definitions.hpp"

using namespace std;

class ShaderCompiler {
public:

    void LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath);
    void CompileShaders();

    void Run();
    GLuint GetShaderID();

    void SetBool(const string &name, bool value);
    void SetInt(const string &name, int value);
    void SetFloat(const string &name, float value);

    void Delete();
    
private:
    string vertexCode;
    string fragmentCode;

    GLuint shaderProgram;
};
