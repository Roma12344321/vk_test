#include "VkApp.h"

#include <iostream>

const int VkApp::initialize() {
  if (!glfwInit())
    return -1;

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  window = glfwCreateWindow(640, 480, "Vulkan Demo", nullptr, nullptr);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  return 0;
}

void VkApp::run() {
  while (!glfwWindowShouldClose(window))
    glfwPollEvents();
}

void VkApp::terminate() {
  glfwDestroyWindow(window);
  glfwTerminate();
}
