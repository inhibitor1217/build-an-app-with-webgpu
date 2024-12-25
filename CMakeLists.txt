cmake_minimum_required(VERSION 3.5.0)
project(build-an-app-with-webgpu VERSION 0.1.0 LANGUAGES C CXX)

add_executable(build-an-app-with-webgpu main.cpp)

include(CTest)
enable_testing()
