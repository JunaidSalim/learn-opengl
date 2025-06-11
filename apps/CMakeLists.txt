add_executable(triangle src/triangle.cpp)
add_executable(blendTriangle src/blendTriangle.cpp)
add_executable(rectangle src/rectangle.cpp)
add_executable(temp src/temp.cpp)
add_executable(shadersUniform src/shadersUniform.cpp)
add_executable(shadersClass src/shaders_class.cpp)

target_link_libraries(triangle PRIVATE glad glfw)
target_link_libraries(blendTriangle PRIVATE glad glfw)
target_link_libraries(rectangle PRIVATE glad glfw)
target_link_libraries(temp PRIVATE glad glfw)
target_link_libraries(shadersUniform PRIVATE glad glfw)
target_link_libraries(shadersClass PRIVATE glad glfw shaders)

# Copy shader files to build directory
set(SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders.fs
)

# Copy shaders for executables that need them
add_custom_command(TARGET shadersClass POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:shadersClass>
    COMMENT "Copying shader files to shadersClass build directory"
)

add_custom_command(TARGET shadersUniform POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:shadersUniform>
    COMMENT "Copying shader files to shadersUniform build directory"
)