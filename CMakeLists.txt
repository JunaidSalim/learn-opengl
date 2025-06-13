cmake_minimum_required(VERSION 3.5)

project(OpenGL_Game)

# Use full compiler path
# set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
# set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")

# Use ccache
# set(CCACHE_PROGRAM "ccache")
# if(CCACHE_PROGRAM)
#     message(STATUS "Using ccache: ${CCACHE_PROGRAM}")
#     set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
#     set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
# endif()

# Add this after your project() declaration in CMakeLists.txt

# find_program(CCACHE_FOUND ccache)
# if(CCACHE_FOUND)
#     message(STATUS "ccache found: ${CCACHE_FOUND}")
    
#     # Add MSYS2 compiler paths to environment for ccache
#     set(ENV{PATH} "C:/msys64/ucrt64/bin;C:/msys64/usr/bin;$ENV{PATH}")
    
#     set(CMAKE_C_COMPILER_LAUNCHER ${CCACHE_FOUND})
#     set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_FOUND})
# else()
#     message(WARNING "ccache not found")
# endif()


add_subdirectory(libs)
add_subdirectory(apps)
