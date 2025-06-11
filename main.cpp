#include "app/VkApp.h"
#include <iostream>

int main() {
  VkApp *app = new VkApp();

  try {
    app->initialize();

    app->run();

    app->cleanUp();

    delete app;
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    app->cleanUp();

    delete app;

    return -1;
  }

  return 0;
}
