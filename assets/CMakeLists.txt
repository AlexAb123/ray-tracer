set(SHADER_FILES 
    "shaders/shader.frag"
    "shaders/shader.vert"
)

find_package(Vulkan REQUIRED) 

foreach(RELATIVE_PATH ${SHADER_FILES})
    set(ABSOULUTE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_PATH}")
    get_filename_component(FILENAME ${ABSOULUTE_PATH} NAME)
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    set(OUTPUT_PATH "${OUTPUT_DIR}/${FILENAME}.spv")
    set(COMPILED_SHADERS ${COMPILED_SHADERS} ${OUTPUT_PATH})
	set(COMPILED_SHADERS ${COMPILED_SHADERS} PARENT_SCOPE)
    add_custom_command(
        COMMENT "Compiling shader: ${ABSOULUTE_PATH}"
        OUTPUT ${OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND Vulkan::glslc ${ABSOULUTE_PATH} -o ${OUTPUT_PATH}
        DEPENDS ${ABSOULUTE_PATH}
    )
endforeach()

add_custom_target(Shaders DEPENDS ${COMPILED_SHADERS})