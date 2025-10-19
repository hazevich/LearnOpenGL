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
)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)



foreach(CHAPTER ${CHAPTERS})
	foreach(SECTION ${${CHAPTER}})
		file(GLOB SOURCE_FILES "src/${CHAPTER}/${SECTION}/*.cpp")

		project(${SECTION})

		add_executable(${PROJECT_NAME} ${SOURCE_FILES})

		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glad)

		set_target_properties(${PROJECT_NAME} PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/${CHAPTER}/${SECTION}
		)

		set (SHADERS_PATH ${CMAKE_SOURCE_DIR}/src/${CHAPTER}/${SECTION}/shaders)

		if (EXISTS ${SHADERS_PATH})
			add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADERS_PATH} $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
			)
		endif()

		if (CMAKE_VERSION VERSION_GREATER 3.12)
		  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 23)
		endif()
	endforeach()
endforeach()

# TODO: Add tests and install targets if needed.
