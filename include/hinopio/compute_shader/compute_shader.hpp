#pragma once

#include <GL/glew.h>
#include <fmt/format.h>

#include <concepts>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace hinopio
{
    template <class T>
    concept numeric = std::is_arithmetic_v<T>;

    class ComputeShader
    {
    public:
        ComputeShader(const std::filesystem::path &shader_path) : shader_code(load_shader(shader_path)),
                                                                  compute_program(create_shader())
        {
            glUseProgram(compute_program);
        }

        ~ComputeShader()
        {
            glDeleteProgram(compute_program);
        }

        auto execute(const GLuint ngx = 1, const GLuint ngy = 1, const GLuint ngz = 1) -> void
        {
            glDispatchCompute(ngx, ngy, ngz);
            glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT); // wait
        }

        template <numeric T>
        auto create_buffer(std::vector<T> &data) -> GLuint
        {
            auto ssbo = GLuint{};
            glGenBuffers(1, &ssbo);
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
            glBufferData(GL_SHADER_STORAGE_BUFFER, data.size() * sizeof(T), data.data(), GL_DYNAMIC_COPY);
            glBindBufferBase(GL_SHADER_STORAGE_BUFFER, ssbo_index++, ssbo);
            return ssbo;
        }

        template <numeric T>
        auto read_buffer(const GLuint ssbo, const int n) -> std::vector<T>
        {
            glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
            auto ptr = static_cast<T *>(glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_READ_ONLY));
            if (ptr)
            {
                return std::vector<T>(ptr, ptr + n);
                glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
                glDeleteBuffers(1, &ssbo);
            }
            return {};
        }

        template <typename T>
        auto set_parameter_2f(const std::string &key, const T param1, const T param2) -> void
        {
            auto loc = glGetUniformLocation(compute_program, key.c_str());
            glUniform2f(loc, static_cast<GLfloat>(param1), static_cast<GLfloat>(param2));
        }

    private:
        static auto load_shader(const std::filesystem::path &shader_path) -> std::string
        {
            if (!std::filesystem::exists(shader_path))
            {
                throw std::runtime_error(fmt::format("Failed to open shader file: {}", shader_path.string()));
            }
            auto file = std::ifstream(shader_path);
            return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
        }

        auto create_shader() -> GLuint
        {
            auto shader = glCreateShader(GL_COMPUTE_SHADER);

            const char *src = shader_code.c_str();
            glShaderSource(shader, 1, &src, nullptr);
            glCompileShader(shader);

            auto success = GLint{};
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                char log[512];
                glGetShaderInfoLog(shader, 512, nullptr, log);
                fmt::println("ComputeShader Compilation Error:\n{}", log);
                return 0;
            }

            auto program = glCreateProgram();
            glAttachShader(program, shader);
            glLinkProgram(program);

            glGetProgramiv(program, GL_LINK_STATUS, &success);
            if (!success)
            {
                char log[512];
                glGetProgramInfoLog(program, 512, nullptr, log);
                fmt::println("ComputeShader Program Linking Error:\n{}", log);
                return 0;
            }

            glDeleteShader(shader);
            return program;
        }

        std::string shader_code{};

        GLuint compute_program{};

        GLuint ssbo_index{};
    };
}
