# CMakeList.txt : CMake project for LearnOpenGL, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("LearnOpenGL")


add_subdirectory(dependencies/glfw)
add_subdirectory(dependencies/glad)

add_executable (LearnOpenGL "src/LearnOpenGL.cpp" "src/LearnOpenGL.h")
target_link_libraries(LearnOpenGL PUBLIC glfw)
target_link_libraries(LearnOpenGL PUBLIC glad)


if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET LearnOpenGL PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
