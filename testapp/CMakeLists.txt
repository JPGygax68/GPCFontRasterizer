cmake_minimum_required(VERSION 3.0)

#------------------------------------------------
# Project + basics
#

project(GPCFontRasterizer_TestApp)

#------------------------------------------------
# Configuration
#

#set(LOCSIM_DEV_ROOT "D:/Projects/Locsim" CACHE PATH "Root of Locsim development directory")
	
#------------------------------------------------
# Special settings
#

# Force static runtime libraries
if(0)
FOREACH(flag
  CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
  CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
  CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
  CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
  STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
  SET("${flag}" "${${flag}} /EHsc")
ENDFOREACH()
endif(0)
 
include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)

set(RASTERIZED_FONT_FILE_NAME "arial-14.15.bin")
set(EMBEDDED_DATA_INCLUDE_FILE_NAME "embedded.hpp")

#------------------------------------------------
# Targets
#

set(TEMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp")

set(RASTERIZED_FONT_FILE_PATH "${TEMP_DIR}/${RASTERIZED_FONT_FILE_NAME}")

add_custom_command( OUTPUT "${RASTERIZED_FONT_FILE_PATH}"
	COMMAND GPCFontRasterizer ARGS input=Arial.ttf size=14 size=15 output=${RASTERIZED_FONT_FILE_PATH}
)

set(EMBEDDED_DATA_INCLUDE_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/generated/${EMBEDDED_DATA_INCLUDE_FILE_NAME}")

add_custom_command( OUTPUT "${EMBEDDED_DATA_INCLUDE_FILE_PATH}"
	MAIN_DEPENDENCY "${RASTERIZED_FONT_FILE_PATH}"
	WORKING_DIRECTORY ${TEMP_DIR}
	COMMAND CppFileEmbedder ARGS ${EMBEDDED_DATA_INCLUDE_FILE_PATH} ${RASTERIZED_FONT_FILE_NAME}
)

add_executable(${PROJECT_NAME} WIN32 main.cpp "${EMBEDDED_DATA_INCLUDE_FILE_PATH}")

#add_dependencies(${PROJECT_NAME} ${RASTERIZED_FONT_INCLUDEFILE_FULLPATH})

#------------------------------------------------
# Libraries we need
#

# GPC Fonts

find_package(gpc_fonts REQUIRED NO_CMAKE_ENVIRONMENT_PATH)
target_include_directories(${PROJECT_NAME} PRIVATE ${gpc_fonts_INCLUDE_DIRS})

# SDL2

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})

# OpenGL 

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
