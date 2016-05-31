from conans import ConanFile, CMake

class GPCFontRasterizerConan(ConanFile):
  name = "gpcfontrasterizer"
  version = "0.1"
  settings = "os", "compiler", "build_type", "arch"
  requires = "freetype/2.6.3@lasote/stable", "Boost/1.60.0@lasote/stable", "libGPCFonts/0.1@jpgygax68/alpha", "cereal/0.1@jpgygax68/testing", "zlib/1.2.8@lasote/stable"
  generators = "cmake"
  exports = "main.cpp", "CMakeLists.txt", "cmake"
  default_options = "Boost:shared=False"

  def build(self):
    cmake = CMake(self.settings)
    self.run('cmake %s %s' % (self.conanfile_directory, cmake.command_line))
    self.run("cmake --build . %s" % cmake.build_config)

  def package(self):
    self.copy("*.exe", dst="bin")

  #def package_info(self):
