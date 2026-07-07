cmake_minimum_required(VERSION 3.20)

project(
    WebCamProject
    VERSION 0.1.0
    DESCRIPTION "CMake 기반 Web-Cam Client/Server 프로젝트"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_library(camera_common STATIC
    code/Common/src/build_info.cpp
    code/Common/src/command.cpp
    code/Common/src/error.cpp
)

target_include_directories(camera_common
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/code/Common/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/code/Inc"
)

target_compile_features(camera_common PUBLIC cxx_std_17)

add_executable(camera_client
    code/Client/src/main.cpp
)

target_link_libraries(camera_client
    PRIVATE camera_common
)

add_executable(camera_server
    code/Server/src/main.cpp
)

target_link_libraries(camera_server
    PRIVATE camera_common
)

enable_testing()

find_package(GTest REQUIRED)
include(GoogleTest)

add_executable(camera_tests
    tests/unit/common_build_info_test.cpp
    tests/unit/common_command_test.cpp
    tests/unit/common_error_test.cpp
)

target_link_libraries(camera_tests
    PRIVATE
        camera_common
        GTest::gtest_main
)

gtest_discover_tests(camera_tests)
