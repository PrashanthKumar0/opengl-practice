#ifndef _OPENGL_PRACTICE_TEXTURE2D_HPP_
#define _OPENGL_PRACTICE_TEXTURE2D_HPP_

#include <glad/glad.h>

#include <string>
// #include <>

namespace op
{
    class Texture2D
    {
    public:
        Texture2D(const std::string &filename, bool use_path = false);
        ~Texture2D();

    public:
        // TODO : implment  setTextureDir
        // static auto setTextureDir(std::string &new_shader_base_dir) -> void;
        auto getId() const -> GLuint;
        auto bind(int slot = 0) -> void;

    private:
        static std::string s_texture_base_dir;
        GLuint m_texture_id{};
    };
}

#endif // _OPENGL_PRACTICE_TEXTURE2D_HPP_
