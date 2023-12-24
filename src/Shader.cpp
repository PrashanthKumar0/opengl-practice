#include <glad/glad.h>

#include "opengl_practice/Shader.hpp"

#include <string>
#include <fstream>
#include <stdexcept>

std::string op::Shader::s_shader_base_dir{"./shaders/"};

op::Shader::Shader(const std::string &shader_name)
{
    std::string vs_file_path{s_shader_base_dir + shader_name + ".vs"};
    std::string fs_file_path{s_shader_base_dir + shader_name + ".fs"};

    std::fstream vs_file{vs_file_path};

    if (!vs_file.is_open())
        throw std::runtime_error("vertex shader file " + vs_file_path + " doesn\'t exist.");

    std::fstream fs_file{s_shader_base_dir + shader_name + ".fs"};

    if (!fs_file.is_open())
        throw std::runtime_error("fragment shader file " + fs_file_path + " doesn\'t exist.");

    std::string vs_code{""};
    std::string fs_code{""};

    std::string line{""};

    while (std::getline(vs_file, line))
        vs_code += line + "\n";

    while (std::getline(fs_file, line))
        fs_code += line + "\n";

    GLuint vs_id{createShader(GL_VERTEX_SHADER, vs_code.c_str())};
    GLuint fs_id{createShader(GL_FRAGMENT_SHADER, fs_code.c_str())};

    m_program_id = glCreateProgram();

    glAttachShader(m_program_id, vs_id);
    glAttachShader(m_program_id, fs_id);
    glLinkProgram(m_program_id);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    GLint success{};

    glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(m_program_id, 512, 0, infoLog);
        throw std::runtime_error(std::string{"Failed Linking Shader Program \n"} + infoLog);
    }
}

op::Shader::~Shader()
{
    glDeleteProgram(m_program_id);
}

auto op::Shader::createShader(GLenum shader_type, const char *shader_code) const -> GLuint
{
    GLuint shader_id{glCreateShader(shader_type)};
    glShaderSource(shader_id, 1, &shader_code, nullptr);
    glCompileShader(shader_id);

    GLint success{};

    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader_id, 512, 0, infoLog);
        throw std::runtime_error("Failed compiling " + (getShaderTypeString(shader_type)) + "\n " + infoLog);
    }

    return shader_id;
}

auto op::Shader::getShaderTypeString(GLenum shader_type) const -> std::string
{
    switch (shader_type)
    {
    case GL_VERTEX_SHADER:
        return {"GL_VERTEX_SHADER"};
    case GL_FRAGMENT_SHADER:
        return {"GL_FRAGMENT_SHADER"};
    default:
        return {"<Unknown Shader>"};
    }
}

auto op::Shader::use() -> void
{
    glUseProgram(m_program_id);
}

auto op::Shader::setShaderDir(const std::string &shader_base_dir) -> void
{
    if (!(shader_base_dir.back() == '/' || shader_base_dir.back() == '\\'))
    {
        s_shader_base_dir = shader_base_dir + "/";
    }
    else
    {
        s_shader_base_dir = shader_base_dir;
    }
}
