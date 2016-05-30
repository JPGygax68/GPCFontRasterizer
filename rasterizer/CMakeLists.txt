cmake_minimum_required(VERSION 3.4)

#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/FindFreetype.cmake)
#set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

#------------------------------------------------
# Target: executable
#

project(gpcfontrasterizer)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

file(GLOB SOURCES *.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

#------------------------------------------------
# Libraries
#

# Boost (via Conan)

target_link_libraries(${PROJECT_NAME} ${CONAN_LIBS_BOOST})

# GPC Fonts (via Conan) do not require any configuration, as it's header-only and conan already adds all include dirs

# Cereal (header-only)

if (0)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/external/cereal/include )
else()
target_include_directories(${PROJECT_NAME} PRIVATE ${CONAN_INCLUDE_DIRS_CEREAL})
endif()

# Boost

if (0)
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})
endif()

# FreeType: get the one we built as part of our prereqs

#set(ENV{FREETYPE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../prereqs/install/freetype)
find_package(Freetype REQUIRED)
target_link_libraries(${PROJECT_NAME} ${FREETYPE_LIBRARIES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${FREETYPE_INCLUDE_DIRS})
#target_link_libraries(${PROJECT_NAME} freetype)

if (0)
# Also required for FreeType
add_subdirectory("external/zlib")
if (NOT TARGET zlib)
    message(FATAL_ERROR "zlib is not defined as a target")
endif()
target_link_libraries(${PROJECT_NAME} ${ZLIB_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${ZLIB_INCLUDE_DIRS})
endif()

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
