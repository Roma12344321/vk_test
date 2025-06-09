cmake_minimum_required(VERSION 3.10)

project(vk_first LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(Vulkan REQUIRED)

include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})

file(GLOB VERT_SHADERS "${CMAKE_SOURCE_DIR}/res/shaders/*.vert")
file(GLOB FRAG_SHADERS "${CMAKE_SOURCE_DIR}/res/shaders/*.frag")
set(SHADERS ${VERT_SHADERS} ${FRAG_SHADERS})

set(SPIRV_DIR "${CMAKE_BINARY_DIR}/bin/res/shaders")
file(MAKE_DIRECTORY ${SPIRV_DIR})
find_program(GLSLC_EXECUTABLE glslc REQUIRED)

set(SPV_SHADERS)
foreach(shader IN LISTS SHADERS)
    get_filename_component(name ${shader} NAME_WE)
    set(out_spv "${SPIRV_DIR}/${name}.spv")
    add_custom_command(
            OUTPUT ${out_spv}
            COMMAND ${GLSLC_EXECUTABLE} -o ${out_spv} ${shader}
            DEPENDS ${shader}
            COMMENT "Compiling ${name} → SPIR-V"
    )
    list(APPEND SPV_SHADERS ${out_spv})
endforeach()
add_custom_target(Shaders ALL DEPENDS ${SPV_SHADERS})

file(GLOB_RECURSE CORE_SOURCES "${CMAKE_SOURCE_DIR}/app/*.cpp")
add_library(core STATIC ${CORE_SOURCES})
add_dependencies(core Shaders)
target_include_directories(core PUBLIC
        ${CMAKE_SOURCE_DIR}/app
        ${Vulkan_INCLUDE_DIRS}
)
target_link_libraries(core PUBLIC Vulkan::Vulkan)

add_executable(${PROJECT_NAME} main.cpp)
add_dependencies(${PROJECT_NAME} Shaders)
target_link_libraries(${PROJECT_NAME} PRIVATE core Vulkan::Vulkan)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${SPIRV_DIR}"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>/res/shaders"
        COMMENT "Copy SPIR-V shaders"
)

if(WIN32)
    find_library(GLFW3DLL_LIB
            NAMES glfw3dll
            HINTS ${CMAKE_SOURCE_DIR}
            NO_DEFAULT_PATH
    )
    if(NOT GLFW3DLL_LIB)
        message(FATAL_ERROR "libglfw3dll.a not found in ${CMAKE_SOURCE_DIR}")
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW3DLL_LIB})
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/glfw3.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/"
            COMMENT "Copy GLFW DLL for Windows"
    )

elseif(APPLE)
    find_library(GLFW_DYLIB
        NAMES glfw3 glfw
        PATHS /usr/local/lib /opt/homebrew/lib /usr/lib
    )
    if(NOT GLFW_DYLIB)
        message(FATAL_ERROR "GLFW not found on macOS; please install via Homebrew")
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE
        ${GLFW_DYLIB}
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
        "-framework CoreFoundation"
    )

else()
    find_library(GLFW_SO
            NAMES glfw3 glfw
            PATHS /usr/lib /usr/local/lib
    )
    if(NOT GLFW_SO)
        message(FATAL_ERROR "GLFW not found on Linux; please install libglfw3-dev")
    endif()
    target_link_libraries(${PROJECT_NAME} PRIVATE ${GLFW_SO})
endif()
