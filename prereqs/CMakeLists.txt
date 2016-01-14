cmake_minimum_required(VERSION 3.0)

#------------------------------------------------
# Configure CMake itself
#

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

#------------------------------------------------
# Project + basics
#

project(gpcfontrasterizer-prereqs)

#------------------------------------------------
# Libraries
#

include(ExternalProject)
ExternalProject_Add( freetype

    URL                 http://sourceforge.net/projects/freetype/files/freetype2/2.6.2/freetype-2.6.2.tar.bz2/download
    CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install/freetype"
    #BUILD_COMMAND       ${CMAKE_COMMAND} --build . --target install --config Release
    UPDATE_DISCONNECTED 1
)

ExternalProject_add( gpcbin2c

	GIT_REPOSITORY		git@github.com:JPGygax68/gpcbin2c.git
    CMAKE_ARGS          "-DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/install/gpcbin2c"
    #BUILD_COMMAND       ${CMAKE_COMMAND} --build . --target install --config Release
)

#------------------------------------------------
# Tests
#

enable_testing()

# Not working under Visual Studio: will build the tests but won't run them
#add_custom_target(CHECK COMMAND ${CMAKE_CTEST_COMMAND})

#add_subdirectory(tests)
