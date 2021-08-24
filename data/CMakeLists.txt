add_custom_target(copy-data-files)

set(SHADERS area_light_fragment.glsl deferred_fragment.glsl deferred_vertex.glsl directional_fragment.glsl forward_vertex_only_position.glsl text_fragment.glsl text_vertex.glsl ui_fragment.glsl ui_vertex.glsl)

foreach(shader IN LISTS SHADERS)
	configure_file(${CMAKE_CURRENT_LIST_DIR}/Shaders/${shader} ${PROJECT_SOURCE_DIR}/out/Shaders/${shader} COPYONLY)
endforeach()

set(MESHES Cube.obj Cylinder.obj Sphere.obj UIQuad.obj)

foreach(mesh IN LISTS MESHES)
	configure_file(${CMAKE_CURRENT_LIST_DIR}/Meshes/${mesh} ${PROJECT_SOURCE_DIR}/out/Meshes/${mesh} COPYONLY)
endforeach()

set(TEXTURES DefaultTexture.png)

foreach(texture IN LISTS TEXTURES)
	configure_file(${CMAKE_CURRENT_LIST_DIR}/Textures/${texture} ${PROJECT_SOURCE_DIR}/out/Textures/${texture} COPYONLY)
endforeach()