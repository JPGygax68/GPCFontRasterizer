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

#-----------------------------------------------
# Special settings
#

set(RASTERIZED_FONT_FILENAME "arial-14.15")

#------------------------------------------------
# Targets
#

set(TEMP_DIR "${CMAKE_CURRENT_BINARY_DIR}/tmp")

set(RASTERIZED_FONT_BINARY_FULLPATH "${TEMP_DIR}/${RASTERIZED_FONT_FILENAME}.bin")

add_custom_command( OUTPUT "${RASTERIZED_FONT_BINARY_FULLPATH}"
	COMMAND GPCFontRasterizer ARGS input=Arial.ttf size=14 size=15 output=${RASTERIZED_FONT_BINARY_FULLPATH}
)

set(RASTERIZED_FONT_INCLUDEFILE_FULLPATH "${CMAKE_CURRENT_BINARY_DIR}/generated/${RASTERIZED_FONT_FILENAME}.hpp")

add_custom_command( OUTPUT "${RASTERIZED_FONT_INCLUDEFILE_FULLPATH}"
	MAIN_DEPENDENCY "${RASTERIZED_FONT_BINARY_FULLPATH}"
	WORKING_DIRECTORY ${TEMP_DIR}
	COMMAND CppFileEmbedder ARGS ${RASTERIZED_FONT_INCLUDEFILE_FULLPATH} ${RASTERIZED_FONT_FILENAME}.bin
)

add_executable(${PROJECT_NAME} WIN32 main.cpp "${RASTERIZED_FONT_INCLUDEFILE_FULLPATH}")

#add_dependencies(${PROJECT_NAME} ${RASTERIZED_FONT_INCLUDEFILE_FULLPATH})

#------------------------------------------------
# Libraries we need
#

# SDL2

find_package(SDL2 REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY})

# OpenGL 

find_package(OpenGL)
target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY})
