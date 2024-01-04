// #include <vulkan/vulkan.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class HelloTriangleApplication {
public:
  void run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanup();
  }

private:
  GLFWwindow *window; // actual window

  void initWindow() {
    glfwInit(); // initializes the GLFW library

    // do not create OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable resize
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

  void initVulkan() {

  }

  void mainLoop() {
    // keep the application running until
    // either an error occurs or the window is closed
    while (!glfwWindowShouldClose(window)) { // returns true when window is closed 
      glfwPollEvents(); // checks if any events are triggered
    }

  }

  void cleanup() {
    glfwDestroyWindow(window); // destroys window and frees memory
    glfwTerminate(); // cleans up all GLFW resources
  }
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

