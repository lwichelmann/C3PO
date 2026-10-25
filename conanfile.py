
from conan import ConanFile
from conan.tools.cmake import cmake_layout, CMakeToolchain


class ConanApplication(ConanFile):
    name = "c3po"
    version = "1.0.0"
    package_type = "application"

    settings = "os", "compiler", "build_type", "arch"
    requires = "asio/1.38.2"
    generators = "CMakeDeps"

    def layout(self):
        cmake_layout(self)

    def generate(self):
        tc = CMakeToolchain(self)
        tc.user_presets_path = False
        tc.generate()
