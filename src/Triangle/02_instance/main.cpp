// #include <vulkan/vulkan.h>
// #include <vulkan/vulkan_core.h>

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

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

  VkInstance instance; // connection between application and Vulkan library

  void initWindow() {
    glfwInit(); // initializes the GLFW library

    // do not create OpenGL context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // disable resize
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan", nullptr, nullptr);
  }

  void initVulkan() {
    createInstance(); // create instance
  }

  void mainLoop() {
    // keep the application running until
    // either an error occurs or the window is closed
    while (!glfwWindowShouldClose(window)) { // returns true when window is closed 
      glfwPollEvents(); // checks if any events are triggered
    }

  }

  void cleanup() {
    // all of the other Vulkan resources shuoold be cleaned up before destroying the instance
    vkDestroyInstance(instance, nullptr); // destroy instance, nullptr is a custom allocator callback
    glfwDestroyWindow(window); // destroys window and frees memory
    glfwTerminate(); // cleans up all GLFW resources
  }

  void createInstance() {
    // optional struct to give information about the application
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle"; // name of the application
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0); // version of the application
    appInfo.pEngineName = "No Engine"; // name of the engine
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); // version of the engine
    appInfo.apiVersion = VK_API_VERSION_1_0; // version of the Vulkan API
    
    // Tell the vulkan driver which global extensions and validation layers we want to use
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo; // pointer to the struct with information about the application
    
    uint32_t glfwExtensionCount = 0; // number of extensions
    const char **glfwExtensions; // extensions
    
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount); // get extensions

    createInfo.enabledExtensionCount = glfwExtensionCount; // number of extensions
    createInfo.ppEnabledExtensionNames = glfwExtensions; // extensions
    
    createInfo.enabledLayerCount = 0; // number of validation layers

    /**
      * 1. Pointer to struct with creation info
      * 2. Pointer to custom allocator callbacks
      * 3. Pointer to variable that stores the handle to the new object
      */
    VkResult result = vkCreateInstance(&createInfo, nullptr, &instance); // create instance
    
    if (result != VK_SUCCESS) {
      throw std::runtime_error("failed to create instance!");
    }

    // check if the extensions are supported
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr); // get number of extensions
    std::vector<VkExtensionProperties> extensions(extensionCount); // create vector with extensionCount elements

    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data()); // get extensions
    
    std::cout << "available extensions:" << std::endl;

    for (const auto& extension : extensions) {
      std::cout << "\t" << extension.extensionName << std::endl;
    }

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

