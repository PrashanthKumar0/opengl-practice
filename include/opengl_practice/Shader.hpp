#ifndef _OPENGL_SHADER_WINDOW_HPP_
#define _OPENGL_SHADER_WINDOW_HPP_

#include <glad/glad.h>
#include <string>

namespace op
{

    class Shader
    {

    public:
        Shader(const std::string &shader_name);

    public:
        auto use() -> void;
        static auto setShaderDir(const std::string &shader_base_dir) -> void;

    private:
        auto createShader(GLenum shader_type, const char *shader_code) const -> GLuint;
        auto getShaderTypeString(GLenum shader_type) const -> std::string;

    private:
        static std::string s_shader_base_dir;
        GLuint m_program_id{};
    };

    //
    //
    //
    //
    // ------------- initialize static member ---------

}

#endif // _OPENGL_SHADER_WINDOW_HPP_
