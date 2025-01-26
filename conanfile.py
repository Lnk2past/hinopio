from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMake

class hinopio(ConanFile):
    name = "hinopio"
    version = "0.0.1"
    settings = 'os', 'compiler', 'build_type', 'arch'
    generators = 'CMakeToolchain', 'CMakeDeps'

    def requirements(self):
        self.requires("fmt/11.1.1")
        self.requires("nlohmann_json/3.11.3")
        self.requires("opengl/system")
        self.requires("glew/2.2.0")
        self.requires("glfw/3.4")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def layout(self):
        cmake_layout(self)
