#include <opengl_practice/Window.hpp>
#include <opengl_practice/Shader.hpp>
#include <opengl_practice/Mesh.hpp>
#include <iostream>

int main()
{
    const int window_width{640};
    const int window_height{480};
    op::Window window{window_width, window_height, "Hello Window!"};

    std::vector<op::Mesh::Vertex_t> vertices{
        {{+0.0f, +0.5f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}},
        {{+0.5f, -0.5f, 0.0f}},
    };

    std::vector<op::Mesh::Index_t> indices{0, 1, 2};
    op::Mesh mesh{vertices, indices};

    // Shader relative path with respect to
    // build target directory of "0.3 Shaders" directory
    op::Shader::setShaderDir("./shaders");
    op::Shader flatColorShader{"flatColorShader"};

    glViewport(0, 0, window_width, window_height);
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    while (window.isRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);

        flatColorShader.use();
        mesh.draw();

        window.sync();
    }
}