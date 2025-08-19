cmake_minimum_required (VERSION 3.8)

project ("Renderer")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
	cmake_policy(SET CMP0141 NEW)
	set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")

add_executable (Renderer "src/main.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Renderer PROPERTY CXX_STANDARD 20)
endif()


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