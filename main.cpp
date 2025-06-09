#include "app/VkApp.h"
#include "vulkan/vulkan.hpp"
#include <iostream>

int main() {
  VkApp *app = new VkApp();

  if (app->initialize() != 0) {
    std::cout << "App starting error" << std::endl;

    return -1;
  }

  app->run();

  app->terminate();

  delete app;

  return 0;
}
