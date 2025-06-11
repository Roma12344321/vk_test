#ifndef VKAPP_H
#define VKAPP_H
#define GLFW_INCLUDE_VULKAN

#include "../GLFW/glfw3.h"
#include <vector>

class VkApp {

public:
  int initialize();
  void run();
  void cleanUp();

private:
  GLFWwindow *window;
  VkInstance instance;
  VkDebugUtilsMessengerEXT debugMessenger;

  void initVulkan();
  void createInstance();
  void setupDebugMessenger();
};

#endif
