#------------------------------------------------
# Target: executable
#

set(TARGET_NAME GPCFontRasterizer)

file(GLOB SOURCES *.cpp)

add_executable(${TARGET_NAME} ${SOURCES})

#------------------------------------------------
# Libraries
#

# GPC Fonts

find_package(libGPCFonts REQUIRED NO_CMAKE_ENVIRONMENT_PATH)
target_link_libraries(${TARGET_NAME} libGPCFonts)

# Boost

find_package(boost COMPONENTS filesystem REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${boost_INCLUDE_DIRS})

# FreeType

find_package(FreeType REQUIRED)
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})


#------------------------------------------------
# Exporting the build tree
#

export(TARGETS ${TARGET_NAME} FILE "${TARGET_NAME}-targets.cmake")

# Export the package for use from the build tree
# (registers the build tree with a global CMake registry)
export(PACKAGE ${TARGET_NAME})


# Create a config file for build tree usage:
set(TARGET "${TARGET_NAME}")
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET_LIB_DIR     ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(TARGET_CMAKE_DIR   ${CMAKE_CURRENT_BINARY_DIR})
set(TARGET_EXECUTABLE  ${TARGET_NAME})
configure_file("config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}-config.cmake" @ONLY)

#------------------------------------------------
# Installing
#

# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS ${TARGET_NAME}
	EXPORT ${TARGET_NAME} # create an "export set"
  RUNTIME DESTINATION bin
)

 # Install the export set for use with the install-tree
install(EXPORT ${TARGET_NAME} DESTINATION cmake)
