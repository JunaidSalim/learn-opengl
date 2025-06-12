#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void calculateTextureDimensions(float* vertices, int vertexCount, int stride, float& halfWidth,
                                float& halfHeight);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Movement variables
float offsetX = 0.0f;
float offsetY = 0.0f;
const float moveSpeed = 0.5f;  // units per second

// Dynamic texture boundaries (calculated from vertex data)
float textureHalfWidth = 0.0f;   // will be calculated from vertices
float textureHalfHeight = 0.0f;  // will be calculated from vertices

// Timing variables for frame-rate independent movement
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
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
      // positions       // texture coords
      0.1f,  0.1f,  0.0f, 1.0f, 1.0f,  // top right
      0.1f,  -0.1f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,  // bottom left
      -0.1f, 0.1f,  0.0f, 0.0f, 1.0f   // top left
  };

  // Calculate texture boundaries dynamically from vertex data
  float minX = vertices[0], maxX = vertices[0];  // Start with first X coordinate
  float minY = vertices[1], maxY = vertices[1];  // Start with first Y coordinate

  // Find min/max X and Y from all vertices
  for (int i = 0; i < 4; i++) {
    float x = vertices[i * 5];      // X coordinate (every 5th element starting from 0)
    float y = vertices[i * 5 + 1];  // Y coordinate (every 5th element starting from 1)

    if (x < minX) minX = x;
    if (x > maxX) maxX = x;
    if (y < minY) minY = y;
    if (y > maxY) maxY = y;
  }

  // Calculate half-widths from the min/max values
  textureHalfWidth = (maxX - minX) / 2.0f;
  textureHalfHeight = (maxY - minY) / 2.0f;

  unsigned int indices[] = {
      0, 1, 3,  // first triangle
      1, 2, 3   // second triangle
  };
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  // texture coord attribute
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // set the texture wrapping parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  // set texture filtering parameters
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR);  // load image, create texture and generate mipmaps
  int width, height, nrChannels;

  // Don't flip the image when loading - we'll handle flipping with texture coordinates
  stbi_set_flip_vertically_on_load(true);

  unsigned char* data = stbi_load("texture.jpg", &width, &height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Failed to load texture" << std::endl;
  }
  stbi_image_free(data);
  while (!glfwWindowShouldClose(window)) {
    // Calculate deltaTime for frame-rate independent movement
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // bind Texture
    glBindTexture(GL_TEXTURE_2D, texture);  // render container
    ourShader.use();

    // Set the offset uniform (vec2)
    int offsetLocation = glGetUniformLocation(ourShader.ID, "offset");
    glUniform2f(offsetLocation, offsetX, offsetY);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}

void processInput(GLFWwindow* window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(window, true);

  float movement = moveSpeed * deltaTime;

  // Calculate proper boundaries considering texture size
  float maxX = 1.0f - textureHalfWidth;    // Right boundary
  float minX = -1.0f + textureHalfWidth;   // Left boundary
  float maxY = 1.0f - textureHalfHeight;   // Top boundary
  float minY = -1.0f + textureHalfHeight;  // Bottom boundary

  // Apply movement with proper boundary checking
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) offsetY = std::min(maxY, offsetY + movement);
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) offsetY = std::max(minY, offsetY - movement);
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) offsetX = std::max(minX, offsetX - movement);
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) offsetX = std::min(maxX, offsetX + movement);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}