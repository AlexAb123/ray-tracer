set(SHADERS 
    "shaders/shader.frag"
    "shaders/shader.vert"
)
find_package(Vulkan REQUIRED glslc) 

foreach(RELATIVE_PATH ${SHADERS})
    set(SHADER "${CMAKE_CURRENT_SOURCE_DIR}/${RELATIVE_PATH}")
    get_filename_component(FILENAME ${SHADER} NAME)
    set(OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/shaders")
    set(OUTPUT_PATH "${OUTPUT_DIR}/${FILENAME}.spv")
    set(COMPILED_SHADERS ${COMPILED_SHADERS} ${OUTPUT_PATH})
	set(COMPILED_SHADERS ${COMPILED_SHADERS} PARENT_SCOPE)
    add_custom_command(
        COMMENT "Compiling shader ${SHADER}..."
        OUTPUT ${OUTPUT_PATH}
        COMMAND ${CMAKE_COMMAND} -E make_directory ${OUTPUT_DIR}
        COMMAND Vulkan::glslc ${SHADER} -o ${OUTPUT_PATH}
        DEPENDS ${SHADER}
    )
endforeach()

add_custom_target(Assets DEPENDS ${COMPILED_SHADERS})

# Publish outputs globally so src/ can see them
set_property(GLOBAL PROPERTY ALL_COMPILED_SHADERS "${COMPILED_SHADERS}")

# Helpful debug:
message(STATUS "compiled_shaders (assets): ${COMPILED_SHADERS}")