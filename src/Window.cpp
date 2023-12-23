#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "opengl_practice/Window.hpp"

#include <string_view>
#include <stdexcept>

auto op::Window::initWindow() -> void
{
    if (glfwInit() != GLFW_TRUE)
        throw std::runtime_error("glfwInit() failed");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);

    m_glfwWindow_ptr = glfwCreateWindow(m_window_width, m_window_height, m_window_title.c_str(), nullptr, nullptr);

    if (!m_glfwWindow_ptr)
        throw std::runtime_error("glfw failed creating window");

    glfwMakeContextCurrent(m_glfwWindow_ptr);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw std::runtime_error("glad failed finding opengl.dll proc");
}

op::Window::Window(int width, int height, const std::string_view &title)
    : m_window_width(width),
      m_window_height(height),
      m_window_title(title)
{
    initWindow();
}

op::Window::~Window()
{
    glfwDestroyWindow(m_glfwWindow_ptr);
    glfwTerminate();
}

auto op::Window::isRunning() const -> bool
{
    return !glfwWindowShouldClose(m_glfwWindow_ptr);
}

auto op::Window::sync() const -> void
{
    glfwSwapBuffers(m_glfwWindow_ptr);
    glfwPollEvents();
}