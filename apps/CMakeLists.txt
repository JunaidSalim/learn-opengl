add_executable(movement src/movement/movement.cpp)

target_link_libraries(movement PRIVATE glad glfw shaders stb_image glm-header-only)
target_include_directories(movement PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)

set(SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/shaders.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/shaders/shaders.fs
)

# Copy shaders for executables that need them
add_custom_command(TARGET shadersClass POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:shadersClass>
    COMMENT "Copying shader files to shadersClass build directory"
)