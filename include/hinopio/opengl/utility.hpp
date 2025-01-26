#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <fmt/format.h>

#include <stdexcept>

namespace hinopio
{
    struct GLScope
    {
        GLScope()
        {
            if (!glfwInit())
            {
                fmt::println("Failed to initialize GLFW");
            }

            auto window = glfwCreateWindow(1, 1, "compute", nullptr, nullptr);
            if (!window)
            {
                glfwTerminate();
                throw std::runtime_error("Failed to create GLFW window");
            }
            glfwMakeContextCurrent(window);

            glewExperimental = GL_TRUE;
            if (glewInit() != GLEW_OK)
            {
                throw std::runtime_error("Failed to initialize GLEW");
            }
        }

        ~GLScope()
        {
            glfwTerminate();
        }
    };
    }