# CMakeLists.txt for the Coordinate

add_executable(coordinate src/coordinate/coordinate.cpp)

target_link_libraries(coordinate PRIVATE glad glfw shaders stb_image glm-header-only)
target_include_directories(coordinate PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)

# Set custom output directory for coordinate executable
set_target_properties(coordinate PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps/coordinate
    RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/apps/coordinate
    RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/apps/coordinate
)

set(SHADER_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate/shader.vs
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate/shader.fs
)

set(TEXTURE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/coordinate/texture.jpg
)

# Copy shaders for executables that need them
add_custom_command(TARGET coordinate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${SHADER_FILES}
    ${CMAKE_BINARY_DIR}/apps/coordinate
    COMMENT "Copying shader files to coordinate build directory"
)

# Copy texture files for executables that need them
add_custom_command(TARGET coordinate POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${TEXTURE_FILES}
    ${CMAKE_BINARY_DIR}/apps/coordinate
    COMMENT "Copying texture files to coordinate build directory"
)


# # Cmake for pad
# add_executable(pad src/pad/pad.cpp)

# target_link_libraries(pad PRIVATE glad glfw shaders)

# set(SHADER_FILES
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/pad/shader.vs
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/pad/shader.fs
# )

# # Copy shaders for executables that need them
# add_custom_command(TARGET pad POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${SHADER_FILES}
#     $<TARGET_FILE_DIR:pad>
#     COMMENT "Copying shader files to pad build directory"
# )


# CMake for Movement

# add_executable(movement src/movement/movement.cpp)

# target_link_libraries(movement PRIVATE glad glfw shaders stb_image glm-header-only)
# target_include_directories(movement PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)

# set(SHADER_FILES
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/shader.vs
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/shader.fs
# )

# set(TEXTURE_FILES
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/movement/texture.jpg
# )

# # Copy shaders for executables that need them
# add_custom_command(TARGET movement POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${SHADER_FILES}
#     $<TARGET_FILE_DIR:movement>
#     COMMENT "Copying shader files to movement build directory"
# )

# # Copy texture files for executables that need them
# add_custom_command(TARGET movement POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${TEXTURE_FILES}
#     $<TARGET_FILE_DIR:movement>
#     COMMENT "Copying texture files to movement build directory"
# )
