#include "Window.hpp"

Window::Window(int width, int height, const std::string &title)
    : _width(width), _height(height)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if (!(_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr))) {
        glfwTerminate();
        throw std::runtime_error("Failed to create window");
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        throw std::runtime_error("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
}

Window::~Window()
{
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void Window::update()
{
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

void Window::clear(int r, int g, int b)
{
    glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::close()
{
    glfwSetWindowShouldClose(_window, true);
}

bool Window::is_open() const
{
    return !glfwWindowShouldClose(_window);
}

bool Window::is_key_pressed(int key) const
{
    return glfwGetKey(_window, key) == GLFW_PRESS;
}
