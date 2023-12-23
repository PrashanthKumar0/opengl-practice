#include <opengl_practice/Window.hpp>
#include <iostream>

int main()
{
    const int window_width{640};
    const int window_height{480};
    op::Window window{window_width, window_height, "Hello Window!"};
    // window.onResize([](op::Window &window)
    //                 {
    //                     const int width{window.getWidth()};
    //                     const int height{window.getHeight()};
    //                     std::cout << "Resize : < " << width << " , " << height << " >\n"; //
    //                 });

    glViewport(0, 0, window_width, window_height);
    glClearColor(0.1f, 0.2f, 0.2f, 1.0f);

    while (window.isRunning())
    {
        glClear(GL_COLOR_BUFFER_BIT);


        window.sync();
    }
}