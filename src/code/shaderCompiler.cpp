#include "../headers/shaderCompiler.hpp"

void ShaderCompiler::LoadShaders(const GLchar* vertexPath, const GLchar* fragmentPath)
{
    // -----------------------------------------
    //
    //    VERTEX SHADER STUFF
    //
    // -----------------------------------------

    std::ifstream vertexShaderFile;
    vertexShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        vertexShaderFile.open(vertexPath);
        std::stringstream vertexShaderStream;

        // Read file's buffer contents into streams
        vertexShaderStream << vertexShaderFile.rdbuf();
        vertexShaderFile.close();

        vertexCode = vertexShaderStream.str();
        cout << "[OK] VERT CODE READ" << endl;
    }
    catch (std::ifstream::failure e)
    {
        cout << "ERROR: IMPOSSIBLE TO READ VERTEX SHADER FILE" << endl;
    }

    // -----------------------------------------
    //
    //    FRAGMENT SHADER STUFF
    //
    // -----------------------------------------

    std::ifstream fragmentShaderFile;
    fragmentShaderFile.exceptions(std::ifstream::badbit);

    try
    {
        fragmentShaderFile.open(fragmentPath);
        std::stringstream fragmentShaderStream;

        // Reading file's buffer contents into streams
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        fragmentShaderFile.close();
        fragmentCode = fragmentShaderStream.str();

        cout << "[OK] FRAG CODE READ" << endl;
    }
    catch (std::ifstream::failure e)
    {
        cout << "ERROR: IMPOSSIBLE TO READ FRAGMENT SHADER FILE" << endl;
    }
}

void ShaderCompiler::CompileShaders()
{
    // Setting our source to our shaderfiles' output strings + conversion from string to char
    const GLchar* vertexShaderSource = vertexCode.c_str();
    const GLchar* fragmentShaderSource = fragmentCode.c_str();

    /* SHADER COMPILATION */
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Checking for a successful shader compilation
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_ERROR \n" << infoLog << std::endl;
    }
    else
    {
        cout << "[OK] VERT CODE COMPILATION" << endl;
    }
    

    // FRAGMENT SHADER
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_ERROR \n" << infoLog << std::endl;
    }
    else
    {
        cout << "[OK] FRAG CODE COMPILATION" << endl;
    }
    

    // LINKING OUR TWO SHADERS
    shaderProgram = glCreateProgram();

    cout << "[OK] CREATED SHADER PROGRAM" << endl;
    cout << "ATTEMPTING TO LINK SHADERS..." << endl;

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Checking for any linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED \n" << infoLog << std::endl;
    }
    else
    {
        cout << "[OK] SUCCESSFULLY LINKED SHADERS" << endl;

        // Our vert + frag shaders are now a program so we can delete them
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        cout << "[OK] DELETING NO LONGER NEEDED SHADERS" << endl;
    }
    
}

void ShaderCompiler::Run()
{
    glUseProgram(shaderProgram);
}

GLuint ShaderCompiler::GetShaderID() 
{
    return shaderProgram;
}

void ShaderCompiler::SetBool(const string &name, bool value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
}

void ShaderCompiler::SetInt(const string &name, int value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void ShaderCompiler::SetFloat(const string &name, float value)
{
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void ShaderCompiler::Delete()
{
    glDeleteProgram(shaderProgram);
}