from conans import ConanFile, CMake


class GPCFontRasterizerConan(ConanFile):
    name = "gpcfontrasterizer"
    version = "0.1.2"
    url = "https://github.com/JPGygax68/GPCFontRasterizer.git"
    settings = "os", "compiler", "arch"  # , "build_type"
    requires = (("freetype/2.10.1", "private"),
                ("Boost/1.60.0@lasote/stable", "private"),
                ("libGPCFonts/0.1.1@JPGygax68/alpha", "private"),
                ("cereal/0.1@JPGygax68/testing", "private"))
    generators = "cmake"
    exports = "main.cpp", "CMakeLists.txt", "cmake"
    default_options = "Boost:shared=False"

    def config(self):
        print "self.settings.compiler[\"Visual Studio\"]:"
        print self.settings.compiler["Visual Studio"]
        self.settings.compiler["Visual Studio"].remove("runtime")

    def build(self):
        cmake = CMake(self.settings)
        self.run("cmake %s %s" %
                 (self.conanfile_directory, cmake.command_line))
        self.run("cmake --build . --config Release")

    def package(self):
        # TODO: equivalent for non-Windows ?
        self.copy("*.exe", dst=".")

    def conan_info(self):
        # This is an executable tool, build type does not matter
        self.info.settings.build_type = "Release"

    # def package_info(self):
