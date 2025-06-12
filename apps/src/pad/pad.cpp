#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>
#include <iostream>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

float offsetX = 0.0f;
float offsetY = 0.0f;
const float moveSpeed = 0.5f;

float textureHalfWidth = 0.0f;
float textureHalfHeight = 0.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Brick Breaker", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  Shader ourShader("shader.vs", "shader.fs");

  float vertices[] = {
      // positions
      0.15f,  -0.9f, 0.0f,  // top right
      0.15f,  -1.0f, 0.0f,  // bottom right
      -0.15f, -1.0f, 0.0f,  // bottom left
      -0.15f, -0.9f, 0.0f   // top left
  };

  unsigned int indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };

  float minX = vertices[0], maxX = vertices[0];  // Start with first X coordinate
  float minY = vertices[1], maxY = vertices[1];  // Start with first Y coordinate

  for (int i = 0; i < 4; i++) {
    float x = vertices[i * 3];      // X coordinate (every 5th element starting from 0)
    float y = vertices[i * 3 + 1];  // Y coordinate (every 5th element starting from 1)

    if (x < minX) minX = x;
    if (x > maxX) maxX = x;
    if (y < minY) minY = y;
    if (y > maxY) maxY = y;
  }

  textureHalfWidth = (maxX - minX) / 2.0f;
  textureHalfHeight = (maxY - minY) / 2.0f;

  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();

    int offsetLocation = glGetUniformLocation(ourShader.ID, "offset");
    glUniform2f(offsetLocation, offsetX, offsetY);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

  float movement = moveSpeed * deltaTime;

  float maxX = 1.0f - textureHalfWidth;   // Right boundary
  float minX = -1.0f + textureHalfWidth;  // Left boundary

  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) offsetX = std::max(minX, offsetX - movement);
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) offsetX = std::min(maxX, offsetX + movement);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}