# CMakeList.txt : CMake project for Renderer, include source and define
# project specific logic here.



# Add source to this project's executable.
add_executable (Renderer "CPU/renderer.cpp" "CPU/renderer.h" "CPU/hittable.h" "CPU/hittable_list.h" "CPU/ray.h" "CPU/vector3.h" "CPU/sphere.h" "CPU/utils.h" "CPU/interval.h" "CPU/camera.h" "CPU/camera.cpp" "CPU/interval.cpp" "CPU/material.h" "main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

# Add the include directory
target_include_directories(Renderer PRIVATE 
    "${CMAKE_SOURCE_DIR}/dependencies/include"
)

# Link libraries
target_link_libraries(Renderer PRIVATE 
    "${CMAKE_SOURCE_DIR}/dependencies/lib/glfw3.lib"
    opengl32
    user32  
    gdi32
)

find_package(Vulkan REQUIRED)
target_include_directories(Renderer PRIVATE ${Vulkan_INCLUDE_DIRS})
target_link_libraries(Renderer PRIVATE ${Vulkan_LIBRARIES})