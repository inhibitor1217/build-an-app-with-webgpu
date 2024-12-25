cmake_minimum_required(VERSION 3.5.0)
project(build-an-app-with-webgpu VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)

add_executable(build-an-app-with-webgpu main.cpp)

set(DAWN_FETCH_DEPENDENCIES ON)
add_subdirectory("dawn" EXCLUDE_FROM_ALL)
target_link_libraries(build-an-app-with-webgpu PRIVATE dawn::webgpu_dawn glfw webgpu_glfw)

include(CTest)
enable_testing()
