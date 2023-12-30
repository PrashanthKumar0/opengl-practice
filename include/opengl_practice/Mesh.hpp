#ifndef _OPENGL_PRACTICE_MESH_HPP_
#define _OPENGL_PRACTICE_MESH_HPP_

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <vector>

namespace op
{
    class Mesh
    {

    public:
        struct Vertex
        {
            glm::vec3 Position{};
            glm::vec3 Normal{};
            glm::vec2 TextureCoord{};
        };

    public:
        using Vertex_t = Vertex;
        using Index_t = GLuint;

    public:
        Mesh(std::vector<Vertex_t> &vertices, std::vector<Index_t> &indices);
        ~Mesh();

    public:
        auto draw() -> void;

    private:
        GLsizei m_num_indices{};

        GLuint m_VAO;
        GLuint m_VBO;
        GLuint m_EBO;
    };
}

#endif // _OPENGL_PRACTICE_MESH_HPP_
