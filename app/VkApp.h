#ifndef VKAPP_H
#define VKAPP_H
#define GLFW_INCLUDE_VULKAN

#include "../GLFW/glfw3.h"
#include <vector>

class VkApp {

public:
  int initialize();
  void run();
  void terminate();

private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;
  
std::vector<const char*> getRequiredExtensions();
  void initVulkan();
  void createInstance();
  bool checkValidationLayerSupport();
  void setupDebugMessenger();
};

#endif
