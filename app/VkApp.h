#ifndef VKAPP_H
#define VKAPP_H

#include "../GLFW/glfw3.h"

class VkApp {

public:
  const int initialize();
  void run();
  void terminate();

private:
  GLFWwindow *window;
};

#endif
