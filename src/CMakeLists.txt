#------------------------------------------------
# Target: executable
#

file(GLOB SOURCES *.cpp)

add_executable(GPCFontRasterizer ${SOURCES})

#------------------------------------------------
# Libraries
#

# GPC Fonts

find_package(gpc_fonts REQUIRED NO_CMAKE_ENVIRONMENT_PATH)
#message("gpc_fonts include dirs: " ${gpc_fonts_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${gpc_fonts_INCLUDE_DIRS})

# Boost

find_package(boost COMPONENTS filesystem REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})

# FreeType

find_package(FreeType REQUIRED)
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})

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
