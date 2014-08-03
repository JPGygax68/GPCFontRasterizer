cmake_minimum_required(VERSION 3.0)

#------------------------------------------------
# Configure CMake itself
#

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake ${CMAKE_MODULE_PATH})

#------------------------------------------------
# Project + basics
#

project(GPCFontRasterizer)

set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_VERSION 0)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

#-----------------------------------------------
# Installation paths
#

# Offer the user the choice of overriding the installation directories
#set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
#set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
	set(DEF_INSTALL_CMAKE_DIR CMake)
else()
	set(DEF_INSTALL_CMAKE_DIR lib/CMake/${PROJECT_NAME})
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
	set(var INSTALL_${p}_DIR)
	if(NOT IS_ABSOLUTE "${${var}}")
		set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
	endif()
endforeach()

#------------------------------------------------
# Libraries
#

include_directories( ${CMAKE_SOURCE_DIR}/3rdparty/cereal/include )

#------------------------------------------------
# Tools
#

add_subdirectory(3rdparty/CppFileEmbedder/src) # TODO: provide a top-level CMakeLists.txt

#------------------------------------------------
# Target: executable
#

add_subdirectory(src)

#------------------------------------------------
# Target: test app
#

add_subdirectory(testapp)

#------------------------------------------------
# Tests
#

enable_testing()

# Not working under Visual Studio: will build the tests but won't run them
#add_custom_target(CHECK COMMAND ${CMAKE_CTEST_COMMAND})

#add_subdirectory(tests)
