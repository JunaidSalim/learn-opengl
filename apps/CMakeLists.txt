add_executable(triangle src/triangle.cpp)
add_executable(blendTriangle src/blendTriangle.cpp)

target_link_libraries(triangle PRIVATE glad glfw)
target_link_libraries(blendTriangle PRIVATE glad glfw)