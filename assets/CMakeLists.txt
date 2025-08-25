set(SHADER_FILES 
    "shaders/shader.frag"
    "shaders/shader.vert"
)

find_package(Vulkan REQUIRED) 

get_filename_component(CURRENT_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)

foreach(RELATIVE_PATH ${SHADER_FILES})
    set(ABSOULUTE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_PATH}")
    get_filename_component(FILENAME ${ABSOULUTE_PATH} NAME)
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    set(OUTPUT_PATH "${OUTPUT_DIR}/${FILENAME}.spv")
    set(COMPILED_SHADERS ${COMPILED_SHADERS} ${OUTPUT_PATH})
	set(COMPILED_SHADERS ${COMPILED_SHADERS} PARENT_SCOPE)
    add_custom_command(
        COMMENT "Compiling shader ${CURRENT_DIR_NAME}/${RELATIVE_PATH}"
        OUTPUT ${OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND Vulkan::glslc ${ABSOULUTE_PATH} -o ${OUTPUT_PATH}
        DEPENDS ${ABSOULUTE_PATH}
    )
endforeach()

add_custom_target(Shaders DEPENDS ${COMPILED_SHADERS})

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_target(Assets
        DEPENDS Shaders
        COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different "${CMAKE_SOURCE_DIR}/${CURRENT_DIR_NAME}" "${CMAKE_BINARY_DIR}/${CURRENT_DIR_NAME}"
        COMMENT "Copying assets to build directory"
    )
else()
    add_custom_target(Assets
        DEPENDS Shaders
    )
endif()