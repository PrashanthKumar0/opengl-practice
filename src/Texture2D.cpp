#include <glad/glad.h>
#include "opengl_practice/Texture2D.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#endif // STB_IMAGE_IMPLEMENTATION

#include <stdexcept>

std::string op::Texture2D::s_texture_base_dir{"res/textures/"};

op::Texture2D::Texture2D(const std::string &filename, bool use_path)
{

    // stbi load

    GLint image_width{};
    GLint image_height{};
    GLenum image_format{};
    int image_components{};
    // stbi_set_flip_vertically_on_load(true);

    GLubyte *image_data{stbi_load((s_texture_base_dir + filename).c_str(), &image_width, &image_height, &image_components, 0)};

    switch (image_components)
    {
    case 1:
        image_format = GL_RED;
        break;
    case 3:
        image_format = GL_RGB;
        break;
    case 4:
        image_format = GL_RGBA;
        break;
    default:
        throw std::runtime_error("unknown texture format for \n Texture Name : ( " + filename + " ) \nnum components : " + std::to_string(image_components));
    }

    // ------------------
    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, image_format, image_width, image_height, 0, image_format, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    //-------------------

    stbi_image_free(image_data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

auto op::Texture2D::bind(int slot) const -> void
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

op::Texture2D::~Texture2D()
{
    glDeleteTextures(1, &m_texture_id);
}

auto op::Texture2D::setTextureDir(std::string &new_shader_base_dir) -> void
{
    if (
        (*(new_shader_base_dir.end()) == '/') ||
        (*(new_shader_base_dir.end()) == '\\'))
    {
        s_texture_base_dir = new_shader_base_dir;
    }
    else
    {
        s_texture_base_dir = new_shader_base_dir + "/";
    }
}

auto op::Texture2D::getId() const -> GLuint
{
    return m_texture_id;
}
