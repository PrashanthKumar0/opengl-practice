#include "opengl_practice/Mesh.hpp"
#include <vector>
#include <glm/glm.hpp>

op::Mesh::Mesh(std::vector<Vertex_t> &vertices, std::vector<Index_t> &indices)
    : m_num_indices(indices.size())
{
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
    glGenVertexArrays(1, &m_VAO);

    glBindVertexArray(m_VAO);
    //------------------------
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    //------------------------------------------

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex_t) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index_t) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), reinterpret_cast<void *>(offsetof(Vertex_t, Position)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), reinterpret_cast<void *>(offsetof(Vertex_t, Normal)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex_t), reinterpret_cast<void *>(offsetof(Vertex_t, TextureCoord)));
    glEnableVertexAttribArray(2);

    //------------------------------------------
    glBindVertexArray(0);
    //-----------------------
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

op::Mesh::~Mesh()
{

    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
    glDeleteVertexArrays(1, &m_VAO);
}

void op::Mesh::draw()
{
    glBindVertexArray(m_VAO);

    glDrawElements(GL_TRIANGLES, m_num_indices, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);
}
