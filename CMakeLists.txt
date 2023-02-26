cmake_minimum_required(VERSION 3.24 FATAL_ERROR)
project(ip_labs_cpp_23
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if (" ${CMAKE_SOURCE_DIR}" STREQUAL " ${CMAKE_BINARY_DIR}")
    message(
            FATAL_ERROR
            "FATAL: In-source builds are not allowed. You should create a separate directory for build files."
    )
endif ()

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "Build type not specified: Use Release by default")
endif ()

find_package(OpenCV REQUIRED)

message(STATUS "OpenCV version: ${OpenCV_VERSION}")

add_definitions(-DASSETS_DIR="${CMAKE_SOURCE_DIR}/assets/")

add_executable(${PROJECT_NAME}
        src/file-util.cpp
        src/image-util.cpp
        src/lab.cpp
        src/lab1.cpp
        src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
