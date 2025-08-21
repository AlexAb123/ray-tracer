# CMakeList.txt : CMake project for Renderer, include source and define project specific logic here.

# Add source to this project's executable.
add_executable(Renderer "main.cpp")

set_target_properties(Renderer PROPERTIES DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()

# Add the include directory
target_include_directories(Renderer PRIVATE 
    "${CMAKE_SOURCE_DIR}/dependencies/include"
)

find_package(Vulkan REQUIRED)

# Link libraries
target_link_libraries(Renderer PRIVATE 
    "${CMAKE_SOURCE_DIR}/dependencies/lib/glfw3.lib"
    opengl32
    user32  
    gdi32
    Vulkan::Vulkan
)