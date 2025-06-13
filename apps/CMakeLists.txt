# CMakeLists.txt for Apps - Loop-based approach for all executables

# Function to create an executable with its resources
function(create_app_executable APP_NAME)
    # Get the source directory for this app
    set(APP_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/${APP_NAME})
    
    # Find all .cpp files in the app directory
    file(GLOB APP_SOURCES "${APP_SRC_DIR}/*.cpp")
    
    # Create executable for each .cpp file found
    foreach(SOURCE_FILE ${APP_SOURCES})
        # Get the filename without extension to use as executable name
        get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)
        
        # Create the executable
        add_executable(${EXEC_NAME} ${SOURCE_FILE})        # Determine which libraries to link based on app requirements
        if(${APP_NAME} MATCHES "coordinate|movement|texture|transformations|pad|mov3d")
            # Apps that need texture support and GLM
            target_link_libraries(${EXEC_NAME} PRIVATE glad glfw shaders stb_image glm-header-only)
            target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)
        elseif(${APP_NAME} MATCHES "shaders")
            # Apps that need shaders and GLM
            target_link_libraries(${EXEC_NAME} PRIVATE glad glfw shaders glm-header-only)
            target_include_directories(${EXEC_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/libs/external_libs)
        else()
            # Basic apps
            target_link_libraries(${EXEC_NAME} PRIVATE glad glfw shaders)
        endif()
        
        # Set custom output directory for executable
        set_target_properties(${EXEC_NAME} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps/${EXEC_NAME}
            RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/apps/${EXEC_NAME}
            RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/apps/${EXEC_NAME}
        )
        
        # Find and copy shader files
        file(GLOB SHADER_FILES "${APP_SRC_DIR}/*.vs" "${APP_SRC_DIR}/*.fs")
        if(SHADER_FILES)
            add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${SHADER_FILES}
                ${CMAKE_BINARY_DIR}/apps/${EXEC_NAME}
                COMMENT "Copying shader files to ${EXEC_NAME} build directory"
            )
        endif()
        
        # Find and copy texture files
        file(GLOB TEXTURE_FILES "${APP_SRC_DIR}/*.jpg" "${APP_SRC_DIR}/*.png" "${APP_SRC_DIR}/*.bmp")
        if(TEXTURE_FILES)
            add_custom_command(TARGET ${EXEC_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${TEXTURE_FILES}
                ${CMAKE_BINARY_DIR}/apps/${EXEC_NAME}
                COMMENT "Copying texture files to ${EXEC_NAME} build directory"
            )
        endif()
        
        message(STATUS "Created executable: ${EXEC_NAME} in apps/${EXEC_NAME}/")
    endforeach()
endfunction()

# List of all app directories to process
set(APP_DIRECTORIES
    coordinate
    movement
    pad
    rectangles
    shaders
    temp
    texture
    transformations
    triangles
    mov3d
)

foreach(APP_DIR ${APP_DIRECTORIES})
    if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/${APP_DIR})
        create_app_executable(${APP_DIR})
    endif()
endforeach()
