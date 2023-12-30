#ifndef _OPENGL_PRACTICE_SHADER_HPP_
#define _OPENGL_PRACTICE_SHADER_HPP_

#include <glad/glad.h>
#include <string>

#include "opengl_practice/Texture2D.hpp"

namespace op
{

    class Shader
    {

    public:
        Shader(const std::string &shader_name);
        ~Shader();

    public:
        auto use() -> void;
        auto set(const std::string &p_name, GLint p_value) const -> void;
        static auto setShaderDir(const std::string &shader_base_dir) -> void;

    private:
        auto createShader(GLenum shader_type, const char *shader_code) const -> GLuint;
        auto getShaderTypeString(GLenum shader_type) const -> std::string;

    private:
        static std::string s_shader_base_dir;
        GLuint m_program_id{};
    };
}

#endif // _OPENGL_PRACTICE_SHADER_HPP_
