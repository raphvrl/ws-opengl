#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <stdexcept>

class Window
{
    public:
        Window(int width, int heights, const std::string &title);
        ~Window();

        void update();
        void clear(int r, int g, int b);
        void close();
        bool is_open() const;
        bool is_key_pressed(int key) const;

    private:
        GLFWwindow *_window;
        int _width;
        int _height;
};