// #include <vulkan/vulkan.h>
// #include <vulkan/vulkan_core.h>
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

const std::vector<const char *> validationLayers = {
    "VK_LAYER_KHRONOS_validation"};

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

// proxy function to load the address of the vkCreateDebugUtilsMessengerEXT
VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo,
    const VkAllocationCallbacks *pAllocator,
    VkDebugUtilsMessengerEXT *pDebugMessenger) {

  // look up the address of the function
  // PFN_vkCreateDebugUtilsMessengerEXT is a function pointer type
  auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
      instance, "vkCreateDebugUtilsMessengerEXT");

  if (func != nullptr) {
    return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
  } else {
    return VK_ERROR_EXTENSION_NOT_PRESENT; // the extension is not available
  }
}

// proxy function to load the address of the vkDestroyDebugUtilsMessengerEXT
void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                   VkDebugUtilsMessengerEXT debugMessenger,
                                   const VkAllocationCallbacks *pAllocator) {

  // look up the address of the function
  // PFN_vkDestroyDebugUtilsMessengerEXT is a function pointer type
  auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(
      instance, "vkDestroyDebugUtilsMessengerEXT");

  if (func != nullptr) {
    func(instance, debugMessenger, pAllocator);
  }
}

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
  VkDebugUtilsMessengerEXT debugMessenger; // managed with a handle like
                                           // instance, device, etc.

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
    setupDebugMessenger();
  }

  void setupDebugMessenger() {
    if (!enableValidationLayers) {
      return;
    }

    VkDebugUtilsMessengerCreateInfoEXT createInfo;
    populateDebugMessengerCreateInfo(createInfo);

    if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
      throw std::runtime_error("failed to set up debug messenger!");
    }
  }

  void mainLoop() {
    // keep the application running until
    // either an error occurs or the window is closed
    // returns true when window is closed
    while (!glfwWindowShouldClose(window)) {
      glfwPollEvents(); // checks if any events are triggered
    }
  }

  void cleanup() {
    // all of the other Vulkan resources shuoold be cleaned up before destroying
    // the instance.
    // destroy instance, nullptr is a custom allocator callback

    if (enableValidationLayers) {
      DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroyInstance(instance, nullptr);
    glfwDestroyWindow(window); // destroys window and frees memory
    glfwTerminate();           // cleans up all GLFW resources
  }

  void createInstance() {
    if (enableValidationLayers && !checkValidationLayerSupport()) {
      throw std::runtime_error(
          "validation layers requested, but not available!");
    }

    // optional struct to give information about the application
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Triangle"; // name of the application
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";                // name of the engine
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0); // version of the engine
    appInfo.apiVersion = VK_API_VERSION_1_0; // version of the Vulkan API

    // Tell the vulkan driver which global extensions and validation layers we
    // want to use
    VkInstanceCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo; // pointer to the struct with
                                            // information about the application

    /*
    uint32_t glfwExtensionCount = 0; // number of extensions
    const char **glfwExtensions;     // extensions

    // get extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    // number of extensions
    createInfo.enabledExtensionCount = glfwExtensionCount;
    createInfo.ppEnabledExtensionNames = glfwExtensions; // extensions
    */

    auto requiredExtensions = getRequiredExtensions();
    createInfo.enabledExtensionCount =
        static_cast<uint32_t>(requiredExtensions.size());
    createInfo.ppEnabledExtensionNames = requiredExtensions.data();

    VkDebugUtilsMessengerCreateInfoEXT debugCreateInfo{};

    if (enableValidationLayers) {
      createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
      createInfo.ppEnabledLayerNames = validationLayers.data();

      populateDebugMessengerCreateInfo(debugCreateInfo);
      // pNext: pointer to extension-specific structure
      createInfo.pNext = (VkDebugUtilsMessengerCreateInfoEXT *) &debugCreateInfo;
    } else {
      createInfo.enabledLayerCount = 0; // number of validation layers

      createInfo.pNext = nullptr;
    }

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
    // get number of extensions
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
    // create vector with extensionCount elements
    std::vector<VkExtensionProperties> extensions(extensionCount);

    // get extensions
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount,
                                           extensions.data());

    std::cout << "available extensions:" << std::endl;

    for (const auto &extension : extensions) {
      std::cout << "\t" << extension.extensionName << std::endl;
    }
  }

  void populateDebugMessengerCreateInfo(
      VkDebugUtilsMessengerCreateInfoEXT &createInfo) {
    createInfo = {};
    createInfo.sType =
        VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    // except VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
    // to receive notifications about possible problems
    // while leaving out verbose general debug info.
    createInfo.messageSeverity =
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType =
        VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;
    // Can be used to pass user data to the callback function
    createInfo.pUserData = nullptr; // Optional
  }

  bool checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char *layerName : validationLayers) {
      bool layerFound = false;

      for (const auto &layerProperties : availableLayers) {
        if (strcmp(layerName, layerProperties.layerName) == 0) {
          layerFound = true;
          break;
        }
      }

      if (!layerFound) {
        return false;
      }
    }

    return true;
  }

  std::vector<const char *> getRequiredExtensions() {
    uint32_t glfwExtensionCount = 0; // number of extensions
    const char **glfwExtensions;     // extensions

    // get extensions
    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

    std::vector<const char *> extensions(glfwExtensions,
                                         glfwExtensions + glfwExtensionCount);

    if (enableValidationLayers) {
      // add debug extension
      extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
  }

  /**
   * Debug callback function
   *
   * @param messageSeverity
   *   - VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT
   *     - diagnostic message
   *   - VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT
   *     - informational message like the creation of a resource
   *   - VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT
   *     - message about behavior that is not necessarily an error, but very
   * likely a bug in your application
   *   - VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT
   *     - message about behavior that is invalid and may cause crashes
   * @param messageType
   *   - VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT
   *     - some event has happened that is unrelated to the specification or
   * performance
   *   - VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT
   *     - something has happened that violates the specification or indicates a
   * possible mistake
   *   - VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT
   *     - potential non-optimal use of Vulkan
   * @param pCallbackData
   *   - pMessage: message that has been passed to vkCmdBeginDebugUtilsLabelEXT
   *   - pObjects: array of Vulkan object handles related to the message
   *   - objectCount: number of objects in array
   * @param pUserData: pointer to the data specified during the setup of the
   * callback
   * @return VK_FALSE
   *   - if true, the Vulkan call that triggered the validation layer message
   * will be aborted
   *   - so if you want to ignore a message, return VK_FALSE
   */
  static VKAPI_ATTR VkBool32 VKAPI_CALL
  debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                VkDebugUtilsMessageTypeFlagsEXT messageType,
                const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData,
                void *pUserData) {

    // ignore info messages
    std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

    return VK_FALSE;
  }
};

int main() {
  HelloTriangleApplication app;

  try {
    app.run();
  } catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
