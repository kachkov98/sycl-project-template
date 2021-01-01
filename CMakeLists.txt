cmake_minimum_required(VERSION 3.8)
project(example)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(conan)

find_package(ComputeCpp REQUIRED)
conan_cmake_run(CONANFILE conanfile.txt
                BASIC_SETUP CMAKE_TARGETS
                BUILD missing)

set(SOURCES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})
add_sycl_to_target(TARGET ${PROJECT_NAME} SOURCES ${SOURCES})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
conan_target_link_libraries(${PROJECT_NAME})
