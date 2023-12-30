
#include <opengl_practice/Window.hpp>
#include <opengl_practice/Shader.hpp>
#include <opengl_practice/Mesh.hpp>
#include <opengl_practice/Texture2D.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

int main()
{
    const int window_width{480};
    const int window_height{480};
    op::Window window{window_width, window_height, "Hello Window!"};

    std::vector<op::Mesh::Vertex_t> vertices{
        // bottom left - right triangle
        {{-1.0f, +1.0, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{+1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

        // top right - right triangle
        // {{-1.0f, +1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
        {{+1.0f, +1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
        // {{+1.0f, -1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    };

    std::vector<op::Mesh::Index_t> indices{0, 1, 2, 0, 3, 1};
    op::Mesh mesh{vertices, indices};

    // Shader relative path with respect to
    // build target directory of "0.3 Shaders" directory
    op::Shader::setShaderDir("./res/shaders/");
    op::Shader rotatingTextureShader{"rotatingTexture"};
    // op::Shader textureShader{"flatColorShader"};

    // could setTextureDir for being on safe side
    // op::Texture2D::setTextureDir("./res/textures");
    op::Texture2D tex{"awesomeface.png"};

    glViewport(0, 0, window_width, window_height);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    // glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    // uncomment these two lines to overwrite get src alpha
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    const int tex_slot{0};

    glm::mat4 model{1.0f};
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};

    while (window.isRunning())
    {
        tex.bind(tex_slot);

        glClear(GL_COLOR_BUFFER_BIT);

        model = glm::rotate(model, glm::radians(0.1f), glm::vec3(0.0f, 0.0f, 1.0f));

        glm::mat4 MVP{projection * view * model};

        rotatingTextureShader.use();
        rotatingTextureShader.set("texture", tex_slot);
        rotatingTextureShader.set("MVP", MVP);

        mesh.draw();

        window.sync();
    }
}