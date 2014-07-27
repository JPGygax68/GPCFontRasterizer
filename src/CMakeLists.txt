#------------------------------------------------
# Target: executable
#

file(GLOB SOURCES *.cpp)

add_executable(GPCFontRasterizer ${SOURCES})

#------------------------------------------------
# Installing
#

# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS GPCFontRasterizer
	EXPORT GPCFontRasterizer # create an "export set"
  RUNTIME DESTINATION bin
)

 # Install the export set for use with the install-tree
install(EXPORT GPCFontRasterizer DESTINATION cmake)

#------------------------------------------------
# Exporting the build tree
#

# Export the package for use from the build tree
# (registers the build tree with a global CMake registry)
export(PACKAGE GPCFontRasterizer)
