set(SHADER_FILES 
    "shaders/shader.frag"
    "shaders/shader.vert"
)

find_package(Vulkan REQUIRED) 

foreach(RELATIVE_PATH ${SHADER_FILES})
    set(SHADER "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_PATH}")
    get_filename_component(FILENAME ${SHADER} NAME)
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    set(OUTPUT_PATH "${OUTPUT_DIR}/${FILENAME}.spv")
    set(COMPILED_SHADERS ${COMPILED_SHADERS} ${OUTPUT_PATH})
	set(COMPILED_SHADERS ${COMPILED_SHADERS} PARENT_SCOPE)
    add_custom_command(
        COMMENT "Compiling shader: ${RELATIVE_PATH}"
        OUTPUT ${OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND Vulkan::glslc ${SHADER} -o ${OUTPUT_PATH}
        DEPENDS ${SHADER}
    )
endforeach()

add_custom_target(Shaders DEPENDS ${COMPILED_SHADERS})