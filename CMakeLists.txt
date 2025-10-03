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
	getting_started)

set(getting_started
	creating_a_window)

add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)


foreach(CHAPTER ${CHAPTERS})
	foreach(SECTION ${${CHAPTER}})
		file(GLOB SOURCE_FILES "src/${CHAPTER}/${SECTION}/*.cpp")

		project(${SECTION})

		add_executable(${SECTION} ${SOURCE_FILES})

		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glfw)
		target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC glad)

		if (CMAKE_VERSION VERSION_GREATER 3.12)
		  set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 20)
		endif()
	endforeach()
endforeach()

# TODO: Add tests and install targets if needed.
