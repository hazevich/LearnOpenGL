# CMakeList.txt : CMake project for LearnOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

set(CHAPTERS
	1_getting_started)

set(1_getting_started
	1.1_creating_a_window
	2.1_hello_window
	3.1_hello_triangle
	3.2_hello_triangle_ebo
	3.3_hello_triangle_excercise_1
	3.4_hello_triangle_excercise_2
	3.4_hello_triangle_excercise_3
	4.1_shaders_vertex_color
	4.2_shaders_uniforms
	4.3_shaders_more_attributes
	4.4_shaders_shader_class
	4.5_shaders_excercise_1
	4.6_shaders_excercise_2
	4.7_shaders_excercise_3
	5.1_textures
	5.2_two_textures
	5.3_textures_excercise_1
	5.4_textures_excercise_2
	5.5_textures_excercise_3
	5.6_textures_excercise_3.1
	5.7_textures_excercise_4
	6.1_transformations
	6.2_transformations_excercise_1
	6.3_transformations_excercise_2
	7.1_coordinate_systems
	7.2_coordinate_systems_more_3d
)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glm)

add_library(stb_image src/stb_image.cpp)


foreach(CHAPTER ${CHAPTERS})
	foreach(SECTION ${${CHAPTER}})
		file(GLOB SOURCE_FILES 
			"src/${CHAPTER}/${SECTION}/*.h"
			"src/${CHAPTER}/${SECTION}/*.cpp"
		)

		project(${SECTION})

		add_executable(${PROJECT_NAME} ${SOURCE_FILES})

		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glad)
		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glm)
		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC stb_image)

		set_target_properties(${PROJECT_NAME} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CHAPTER}/${SECTION}
		)

		set (SHADERS_PATH ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION}/shaders)

		if (EXISTS ${SHADERS_PATH})
			add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
			)
		endif()

		set (ASSETS_PATH ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION}/assets)

		if (EXISTS ${ASSETS_PATH})
			add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${ASSETS_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
			)
		endif()

		if (CMAKE_VERSION VERSION_GREATER 3.12)
		  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 23)
		endif()
	endforeach()
endforeach()

include_directories(${CMAKE_SOURCE_DIR}/dependencies/stb)

# TODO: Add tests and install targets if needed.
