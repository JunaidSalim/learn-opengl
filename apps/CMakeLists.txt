add_executable(triangle src/triangle.cpp)
add_executable(blendTriangle src/blendTriangle.cpp)
add_executable(rectangle src/rectangle.cpp)
add_executable(temp src/temp.cpp)

target_link_libraries(triangle PRIVATE glad glfw)
target_link_libraries(blendTriangle PRIVATE glad glfw)
target_link_libraries(rectangle PRIVATE glad glfw)
target_link_libraries(temp PRIVATE glad glfw)