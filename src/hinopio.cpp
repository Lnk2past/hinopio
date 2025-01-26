#include "hinopio/hinopio.hpp"

#include <fmt/format.h>
#include <fmt/ranges.h>

#include <fstream>
#include <ranges>
#include <vector>

auto main(int argc, char** argv) -> int
{
    if (argc == 1)
    {
        return 1;
    }

    // initialize context
    auto gl_scope = hinopio::GLScope{};

    // load shader
    auto compute_shader = hinopio::ComputeShader(argv[1]);

    // -------------------------------------------------------------------------
    // TODO: this is sample code foe the mandelbrot example
    // dims, local sizes, work groups, ...
    const auto ls = 32;
    const auto wgs = 128;
    const auto dim = ls * wgs;
    const auto n = dim * dim;

    // set params
    compute_shader.set_parameter_2f("size", dim, dim);
    compute_shader.set_parameter_2f("cmin", -1.5f, -0.05f);
    compute_shader.set_parameter_2f("cdelta", 0.1f, 0.1f);

    // create buffer
    auto data = std::vector<int>(n, 0);
    auto buffer = compute_shader.create_buffer(data);

    // execute the shader
    compute_shader.execute(wgs, wgs, 1);

    // read the data
    auto new_data = compute_shader.read_buffer<int>(buffer, n);

    // write data to disk
    auto f = std::ofstream{"fractal.dat"};
    for (auto r = 0; r < dim; ++r)
    {
        auto sub = std::ranges::subrange(new_data.begin() + r * dim, new_data.begin() + (r + 1) * dim);
        f << fmt::format("{}\n", fmt::join(sub, ","));
    }
}
