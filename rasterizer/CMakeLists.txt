cmake_minimum_required(VERSION 3.4)

#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFreetype.cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#------------------------------------------------
# Target: executable
#

project(gpcfontrasterizer)

if (EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
  conan_basic_setup()
endif()

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

#------------------------------------------------
# Libraries
#

# Conan-imported libraries:
# Boost, FreeType, libGPCFonts, Cereal

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS})
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_INCLUDE_DIRS})

#-----------------------------------------------
# Testing
#

enable_testing()

#add_custom_target(CHECK COMMAND ${CMAKE_CTEST_COMMAND})

#------------------------------------------------
# Exporting the build tree
#

if (0)
export(TARGETS ${PROJECT_NAME} FILE "${PROJECT_NAME}-targets.cmake")

# Export the package for use from the build tree
# (registers the build tree with a global CMake registry)
export(PACKAGE ${PROJECT_NAME})

# Create a config file for build tree usage:
set(TARGET "${PROJECT_NAME}")
set(TARGET_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(TARGET_LIB_DIR     ${CMAKE_CURRENT_BINARY_DIR}/lib)
set(TARGET_CMAKE_DIR   ${CMAKE_CURRENT_BINARY_DIR})
set(TARGET_EXECUTABLE  ${PROJECT_NAME})
configure_file("config.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}-config.cmake" @ONLY)
endif()

#------------------------------------------------
# Installing
#

if (0)
# Note: we use "gpc" as a vendor prefix (subdir in include directory e.a.)
# TODO: define prefixes in parent CMake list ?

install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME} # create an "export set"
  RUNTIME DESTINATION bin
)

 # Install the export set for use with the install-tree
install(EXPORT ${PROJECT_NAME} DESTINATION cmake)
endif()
