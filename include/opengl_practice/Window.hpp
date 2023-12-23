#ifndef _OPENGL_PRACTICE_WINDOW_HPP_
#define _OPENGL_PRACTICE_WINDOW_HPP_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <functional>
#include <string_view>

namespace op
{

    class Window
    {

    public:
        Window(int width, int height, const std::string_view &title);
        ~Window();

        auto isRunning() const -> bool;
        auto sync() const -> void;

    private:
        auto initWindow() -> void;

    private:
        int m_window_width{};
        int m_window_height{};
        std::string m_window_title{};
        GLFWwindow *m_glfwWindow_ptr{nullptr};
    };
}

#endif // _OPENGL_PRACTICE_WINDOW_HPP_