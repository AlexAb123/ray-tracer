# CMakeList.txt : CMake project for Renderer, include source and define project specific logic here.

# Add source to this project's executable.

set(EXE "Renderer")

add_executable(${EXE} "main.cpp")

add_dependencies(${EXE} Shaders)

set_target_properties(${EXE} PROPERTIES DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${EXE} PROPERTY CXX_STANDARD 20)
endif()

# Add the include directory
target_include_directories(${EXE} PRIVATE 
    
)

find_package(Vulkan REQUIRED)

# vcpkg ports
find_package(glfw3 CONFIG REQUIRED)

# Link libraries
target_link_libraries(${EXE} PRIVATE 
    glfw
    opengl32
    user32  
    gdi32
    Vulkan::Vulkan
)