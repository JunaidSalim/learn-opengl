# Add GLAD
add_subdirectory(glad)

# Add GLFW
add_subdirectory(glfw-3.4)

add_subdirectory(stb_image)

# Add GLM as header-only library
set(GLM_BUILD_LIBRARY OFF CACHE BOOL "" FORCE)
add_subdirectory(glm)