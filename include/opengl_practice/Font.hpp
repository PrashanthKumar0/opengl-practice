#ifndef _OPENGL_PRACTICE_FONT_HPP_
#define _OPENGL_PRACTICE_FONT_HPP_

#include <glad/glad.h>

#include <string>
#include <memory>
#include <unordered_map>

// #ifndef STB_TRUETYPE_IMPLEMENTATION
//     #define STB_TRUETYPE_IMPLEMENTATION
//     #include <stb/stb_truetype.h>
// #endif // STB_TRUETYPE_IMPLEMENTATION

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "opengl_practice/Shader.hpp"
#include "opengl_practice/Mesh.hpp"

namespace op
{

    class Font
    {
    public:
        Font(const std::string &font_file_name)
            : Font(font_file_name, 25){}; // to enable hinting initialize here
        Font(const std::string &font_file_name, unsigned int line_height);
        ~Font();

    public:
        auto setFontSize(unsigned int new_font_size) -> Font &;
        auto setPosition(const glm::vec3 &new_position) -> Font &;
        auto renderText(const std::wstring &text, const Shader &shader) -> Font &;

        static auto setFontDir(const std::string &new_font_base_dir) -> void;

    private:
        auto generateAndCacheTextureFromAscii(unsigned long long ascii) -> void;

    public:
        // TODO : Move this struct out ?
        struct Character
        {
            unsigned long long ascii{};
            GLuint textureID{};
            glm::vec2 size{};
            glm::vec2 bearing{};
            glm::vec2 advance{};
            Character(unsigned long long p_ascii, GLuint p_textureID, const glm::vec2 &p_size, const glm::vec2 &p_bearing, const glm::vec2 &p_advance)
                : ascii(p_ascii),
                  textureID(p_textureID),
                  size(p_size),
                  bearing(p_bearing),
                  advance(p_advance)
            {
            }
            ~Character()
            {
                glDeleteTextures(1, &textureID);
            }
        };

    private:
        using Character_t = Character;

    private:
        unsigned int m_font_size{};
        std::unordered_map<unsigned long long, std::unique_ptr<Character_t>> m_font_character_cache{};

        glm::vec3 m_cursor_position{200.0f, 200.0f, 0.0f};
        glm::vec3 m_writing_direction{1.0f, 0.0f, 0.0f};

        glm::mat4 m_model_matrix{1.0f};
        glm::mat4 m_view_matrix{glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f))};
        glm::mat4 m_projection_matrix{glm::ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.0f, 100.0f)};
        glm::mat4 m_mvp_matrix{1.0f};
        

        float m_font_scaling_factor{2.0f};
        float m_font_scaling_factor_inv{1.0f / m_font_scaling_factor};

        FT_Face m_font_face{};

        static std::string s_fonts_base_dir;
        static FT_Library s_ft_lib; // do this only once

    };
}
#endif // _OPENGL_PRACTICE_FONT_HPP_