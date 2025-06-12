add_executable(texture src/texture/texture.cpp)

target_link_libraries(texture PRIVATE glad glfw shaders stb_image)

set(SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shader.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/shader.fs
)

set(TEXTURE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/texture/texture.jpg
)

# Copy shaders for executables that need them
add_custom_command(TARGET texture POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    $<TARGET_FILE_DIR:texture>
    COMMENT "Copying shader files to texture build directory"
)

# Copy texture files for executables that need them
add_custom_command(TARGET texture POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${TEXTURE_FILES}
    $<TARGET_FILE_DIR:texture>
    COMMENT "Copying texture files to texture build directory"
)
