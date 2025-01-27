#include "hinopio/hinopio.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <fstream>
#include <ranges>
#include <vector>

auto main(int argc, char **argv) -> int
{
    if (argc == 1)
    {
        return 1;
    }

    // initialize context
    auto gl_scope = hinopio::GLScope{};

    // load shader
    auto compute_shader = hinopio::ComputeShader(argv[1]);

    // // -------------------------------------------------------------------------
    // // TODO: this is sample code for the slang example
    auto b1 = std::vector<float>(256, 1.0f);
    auto b2 = std::vector<float>(256, 7.0f);
    auto res = std::vector<float>(256);

    compute_shader.create_buffer(b1);
    compute_shader.create_buffer(b2);
    auto rb = compute_shader.create_buffer(res);

    compute_shader.execute(256, 1, 1);
    auto new_data = compute_shader.read_buffer<float>(rb, 256);
    fmt::println("{}", fmt::join(new_data, ","));

    // // -------------------------------------------------------------------------
    // // TODO: this is sample code for the mandelbrot example
    // // dims, local sizes, work groups, ...
    // const auto ls = 32;
    // const auto wgs = 768;
    // const auto dim = ls * wgs;
    // const auto n = dim * dim;

    // fmt::println("l={}", dim);

    // // set params
    // compute_shader.set_parameter_2f("size", dim, dim);
    // compute_shader.set_parameter_2f("cmin", -1.5f, -1.0f);
    // compute_shader.set_parameter_2f("cdelta", 2.0f, 2.0f);

    // // create buffer
    // auto data = std::vector<int>(n, 0);
    // auto buffer = compute_shader.create_buffer(data);

    // // execute the shader
    // compute_shader.execute(wgs, wgs, 1);

    // // read the data
    // auto new_data = compute_shader.read_buffer<int>(buffer, n);

    // // write data to disk
    // auto f = std::ofstream{"fractal.dat"};
    // for (auto r = 0; r < dim; ++r)
    // {
    //     auto sub = std::ranges::subrange(new_data.begin() + r * dim, new_data.begin() + (r + 1) * dim);
    //     f << fmt::format("{}\n", fmt::join(sub, ","));
    // }
}
