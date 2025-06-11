#ifndef VKAPP_H
#define VKAPP_H
#define GLFW_INCLUDE_VULKAN

#include "../GLFW/glfw3.h"
#include <vector>

class VkApp {

public:
  void initialize();
  void run();
  void cleanUp();

private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

  void initVulkan();
  void createInstance();
  void setupDebugMessenger();
  void pickPhysicalDevice();
};

#endif
