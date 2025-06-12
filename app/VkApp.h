#ifndef VKAPP_H
#define VKAPP_H
#define GLFW_INCLUDE_VULKAN

#include "../GLFW/glfw3.h"

class VkApp {

public:
  void initialize();
  void run();
  void cleanUp();

  VkApp() = default;
  VkApp(const VkApp &) = delete;
  VkApp &operator=(const VkApp &) = delete;
  VkApp(VkApp &&) = delete;
  VkApp &operator=(VkApp &&) = delete;

private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
  VkDevice device;
  VkQueue graphicsQueue;

  void initVulkan();
  void createInstance();
  void setupDebugMessenger();
  void pickPhysicalDevice();
  void createLogicalDevice();
};

#endif
