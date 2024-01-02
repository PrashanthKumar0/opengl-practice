#include <glad/glad.h>

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <utility>
#include <memory>

// #ifndef STB_TRUETYPE_IMPLEMENTATION
//     #define STB_TRUETYPE_IMPLEMENTATION
//     #include <stb/stb_truetype.h>
// #endif // STB_TRUETYPE_IMPLEMENTATION

#include <glm/glm.hpp>

#include "opengl_practice/Font.hpp"
#include "opengl_practice/Shader.hpp"
#include "opengl_practice/Mesh.hpp"

#include <ft2build.h>
#include FT_FREETYPE_H

//-------- INIT STATIC VARS ------------------------------
std::string op::Font::s_fonts_base_dir{"./res/fonts/"};
FT_Library op::Font::s_ft_lib{};

// ---------------------------------------------------

// ----- Methods -------------------------------------
op::Font::Font(const std::string &font_file_name, unsigned int line_height)
{
    static FT_Error error{FT_Init_FreeType(&s_ft_lib)}; // do this only once

    if (error)
        throw std::runtime_error("FT_Init_FreeType failed");

    error = FT_New_Face(s_ft_lib, (s_fonts_base_dir + font_file_name).c_str(), 0, &m_font_face);

    if (error)
        throw std::runtime_error("file " + (s_fonts_base_dir + font_file_name) + " not found or it isnt supported by libfreetype.");

    error = FT_Set_Pixel_Sizes(m_font_face, line_height * m_font_scaling_factor, 0);

    if (error)
        throw std::runtime_error("cant set font\'s line height" + std::to_string(static_cast<int>(line_height)));

    // 36 to 126 are printable characters
    for (unsigned long long ch{36}; ch < 126; ch++)
    { // load first 128 chars
        error = FT_Load_Char(m_font_face, ch, FT_LOAD_RENDER);
        if (error)
            throw std::runtime_error(std::string("failed loading char ascii : " + std::to_string(static_cast<int>(ch))));

        generateAndCacheTextureFromAscii(ch);
    }
}

auto op::Font::generateAndCacheTextureFromAscii(unsigned long long ascii) -> void
{
    const FT_Bitmap bitmap{m_font_face->glyph->bitmap};
    const FT_GlyphSlot glyph{m_font_face->glyph};

    GLuint textureID{};

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, bitmap.width, bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.buffer);

    // glGenerateMipmap(GL_TEXTURE_2D);

    m_font_character_cache[ascii] = std::make_unique<op::Font::Character>(
        ascii,
        textureID,
        glm::vec2{bitmap.width, bitmap.rows} * m_font_scaling_factor_inv,
        glm::vec2{glyph->bitmap_left, glyph->bitmap_top} * m_font_scaling_factor_inv,
        glm::vec2{(glyph->advance.x) / 64.0f, (glyph->advance.y) / 64.0f} * m_font_scaling_factor_inv
        // for weird reason advance moves by 64 characters so divide by 64
    );
}

//----------------------------------------------------------------------
op::Font::~Font()
{
    FT_Done_Face(m_font_face);
    FT_Done_FreeType(s_ft_lib);
}

auto op::Font::setFontSize(unsigned int new_font_size) -> Font &
{

    return (*this);
}

auto op::Font::setPosition(const glm::vec3 &new_position) -> Font &
{

    return (*this);
}

auto op::Font::renderText(const std::wstring &text, const Shader &shader) -> Font &
{

    // glm::scale(model, glm::vec3(ptr_ref.size.x, ptr_ref.size.y, 1.0f))

    shader.use();
    // shader.set("MVP", m_mvp_matrix);
    glm::vec3 cursor_pos{m_cursor_position};

    for (const auto &ch : text)
    {
        if (m_font_character_cache.find(ch) == m_font_character_cache.end())
        {
            FT_Error error{FT_Load_Char(m_font_face, ch, FT_LOAD_RENDER)};
            if (error)
            {
                throw std::runtime_error("Failed rendering character with ascii " + std::to_string(static_cast<unsigned long long>(ch)));
            }
            generateAndCacheTextureFromAscii(ch);
            // continue;
        }
        const Character_t &ptr_ref{*m_font_character_cache[ch].get()};

        glm::vec3 text_pos{ptr_ref.bearing.x, -(ptr_ref.size.y - ptr_ref.bearing.y), 0.0f};

        glm::mat4 model{1.0f};
        model = glm::translate(model, text_pos);
        model = glm::translate(model, cursor_pos);
        model = glm::scale(model, glm::vec3(m_font_scaling_factor_inv, m_font_scaling_factor_inv, 1.0f));

        op::Mesh s_quad_mesh{
            {
                // vertices
                // bottom left - right triangle
                {{0.0f, ptr_ref.size.y * m_font_scaling_factor, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
                {{ptr_ref.size.x * m_font_scaling_factor, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
                {{0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},
                // top right - right triangle
                {{ptr_ref.size.x * m_font_scaling_factor, ptr_ref.size.y * m_font_scaling_factor, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            },
            {0, 1, 2, 0, 3, 1} // indices
        };

        shader.set("MVP", m_projection_matrix * m_view_matrix * model);

        int slot{0}; // TODO : get free slot ( make something like int Texture2D::getFreeSlot(); )
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_font_character_cache[ch].get()->textureID);

        shader.set("bitmap", slot);
        s_quad_mesh.draw();
        cursor_pos += glm::vec3(ptr_ref.advance.x, ptr_ref.advance.y, 0.0f);
    }

    return (*this);
}

auto op::Font::setFontDir(const std::string &new_font_base_dir) -> void
{
}
//----------------------------------------------------------------------