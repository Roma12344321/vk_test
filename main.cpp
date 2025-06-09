#include <vulkan/vulkan.hpp>
#include "app/VkApp.h"
#include "GLFW/glfw3.h"

int main() {
    if (!glfwInit()) {
        return -1;
    }
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Vulkan Demo", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
