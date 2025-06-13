#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_s.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

glm::vec3 objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 objectRotation = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 objectScale = glm::vec3(1.0f, 1.0f, 1.0f);

float moveSpeed = 2.0f;
float rotationSpeed = 90.0f;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Movement3D", NULL, NULL);
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

  // Enable depth testing for 3D
  glEnable(GL_DEPTH_TEST);

  Shader ourShader("shader.vs", "shader.fs");
  float vertices[] = {
      // positions       // texture coords
      0.1f,  0.1f,  0.0f, 1.0f, 1.0f,  // top right
      0.1f,  -0.1f, 0.0f, 1.0f, 0.0f,  // bottom right
      -0.1f, -0.1f, 0.0f, 0.0f, 0.0f,  // bottom left
      -0.1f, 0.1f,  0.0f, 0.0f, 1.0f   // top left
  };
  unsigned int indices[] = {
      0, 1, 2,  // first triangle
      2, 3, 0   // second triangle
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

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
                  GL_REPEAT);  // set texture wrapping to GL_REPEAT (default wrapping method)

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,
                  GL_LINEAR);  // load image, create texture and generate mipmaps
  int width, height, nrChannels;

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
    // Calculate delta time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    processInput(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    ourShader.use();

    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, objectPosition);
    model = glm::rotate(model, glm::radians(objectRotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(objectRotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(objectRotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, objectScale);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection =
        glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

    ourShader.setMat4("model", model);
    ourShader.setMat4("view", view);
    ourShader.setMat4("projection", projection);
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
  if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    objectPosition.x = std::max(-1.0f, objectPosition.x - (moveSpeed * deltaTime));  // Move left
  if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    objectPosition.x = std::min(1.0f, objectPosition.x + (moveSpeed * deltaTime));  // Move right
  if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    objectPosition.y = std::min(1.0f, objectPosition.y + (moveSpeed * deltaTime));  // Move up
  if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    objectPosition.y = std::max(-1.0f, objectPosition.y - (moveSpeed * deltaTime));  // Move down

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    objectRotation.x += rotationSpeed * deltaTime;  // Tilt forward
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    objectRotation.x -= rotationSpeed * deltaTime;  // Tilt backward

  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    objectRotation.y += rotationSpeed * deltaTime;  // Rotate left
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    objectRotation.y -= rotationSpeed * deltaTime;  // Rotate right

  if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
    objectScale += glm::vec3(0.5f * deltaTime);               // Scale up
    if (objectScale.x > 3.0f) objectScale = glm::vec3(3.0f);  // Limit max scale
  }

  if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
    objectScale -= glm::vec3(0.5f * deltaTime);               // Scale down
    if (objectScale.x < 0.1f) objectScale = glm::vec3(0.1f);  // Limit min scale
  }

  // Reset controls (R key)
  if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
    objectPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    objectRotation = glm::vec3(0.0f, 0.0f, 0.0f);
    objectScale = glm::vec3(1.0f, 1.0f, 1.0f);
  }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}