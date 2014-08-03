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
 
#------------------------------------------------
# Sources
#

set(SOURCE_FILES main.cpp)
set(HEADER_FILES )
set(SHADER_FILES )

#------------------------------------------------
# Targets
#

add_executable(${PROJECT_NAME} WIN32 ${SOURCE_FILES})

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
