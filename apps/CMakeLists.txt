add_executable(movement src/movement/movement.cpp)

target_link_libraries(movement PRIVATE glad glfw shaders stb_image glm-header-only)
target_include_directories(movement PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)

set(SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/shader.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/shader.fs
)

set(TEXTURE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/texture.jpg
)

# Copy shaders for executables that need them
add_custom_command(TARGET movement POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:movement>
    COMMENT "Copying shader files to movement build directory"
)

# Copy texture files for executables that need them
add_custom_command(TARGET movement POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${TEXTURE_FILES}
    $<TARGET_FILE_DIR:movement>
    COMMENT "Copying texture files to movement build directory"
)
