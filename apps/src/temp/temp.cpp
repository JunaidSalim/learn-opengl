#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Screen size
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Vertex Shader Source
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;   // Vertex position
layout (location = 1) in vec3 aColor; // Vertex color

out vec3 vertexColor; // Passed to fragment shader

void main()
{
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor; // Pass color to fragment shader
}
)";

// Fragment Shader Source
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;       // Interpolated color
out vec4 FragColor;        // Final output color

void main()
{
    FragColor = vec4(vertexColor, 1.0); // Use interpolated color
}
)";

// Resize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

// Input handler
void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);
}

int main() {
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create window
  GLFWwindow* window =
      glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Interpolated Triangle", NULL, NULL);
  if (!window) {
    std::cout << "Failed to create GLFW window\n";
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Load GLAD
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD\n";
    return -1;
  }

  // Build shaders
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  unsigned int shaderProgram = glCreateProgram();
  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // Triangle vertices: 3D positions + RGB colors
  float vertices[] = {
      // Position           // Color
      -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // Red
      0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // Green
      0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f   // Blue
  };

  // Set up VAO and VBO
  unsigned int VBO, VAO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Vertex positions (location = 0)
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // Vertex colors (location = 1)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Render loop
  while (!glfwWindowShouldClose(window)) {
    processInput(window);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);  // Dark background
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Clean up
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(shaderProgram);

  glfwTerminate();
  return 0;
}
