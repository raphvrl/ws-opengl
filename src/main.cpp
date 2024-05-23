#include <iostream>
#include "Window.hpp"

int main(void)
{
    Window window(800, 600, "OpenGL");

    while (window.is_open()) {
        if (window.is_key_pressed(GLFW_KEY_ESCAPE)) {
            window.close();
        }

        window.clear(0, 0, 0);
        window.update();
    }
    
    return 0;
}
