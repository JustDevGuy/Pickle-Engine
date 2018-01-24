#include "ShaderSource.h"

ShaderSource::ShaderSource(std::string vertexFile, std::string fragmentFile)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char *vertexShaderSource = ReadFile(vertexFile);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderError(vertexShader, GL_COMPILE_STATUS, false, "Error compiling vertex shader");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char *fragmentShaderSource = ReadFile(fragmentFile);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckShaderError(fragmentShader, GL_COMPILE_STATUS, false, "Error compiling fragment shader");

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    BindAttributeLocation(0, "position");
    BindAttributeLocation(1, "texCoord");
    BindAttributeLocation(2, "normal");

    glLinkProgram(program);
    CheckShaderError(program, GL_LINK_STATUS, true, "Error linking program");
}

void ShaderSource::Start()
{
    glUseProgram(program);
}

void ShaderSource::Stop()
{
    glUseProgram(0);
}

void ShaderSource::BindAttributeLocation(int location, std::string variableName)
{
    glBindAttribLocation(program, location, variableName.c_str());
}

const char *ShaderSource::ReadFile(std::string fileName)
{
    std::string content;
    std::fstream fileStream(fileName.c_str(), std::ios::in);

    if(!fileStream.is_open())
    {
        std::cerr << "Could not read file " << fileName.c_str() << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content.c_str();
}

void ShaderSource::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        std::cerr << errorMessage << ": '" << error << "'" << std::endl;
    }
}

int ShaderSource::GetUniformLocation(std::string uniformName)
{
    return glGetUniformLocation(program, uniformName.c_str());
}

void ShaderSource::LoadFloat(int location, float value)
{
    glUniform1f(location, value);
}

void ShaderSource::LoadVector(int location, glm::vec3 value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void ShaderSource::LoadBoolean(int location, bool value)
{
    float toLoad = 0;
    if(value)
        toLoad = 1;
    glUniform1f(location, toLoad);
}

void ShaderSource::LoadMatrix(int location, glm::mat4 value)
{
    glUniformMatrix4fv(location, 1, false, &value[0][0]);
}

void ShaderSource::CleanUp()
{
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
}
