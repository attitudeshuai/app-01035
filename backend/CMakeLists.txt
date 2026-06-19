cmake_minimum_required(VERSION 3.16)

project(ParkingSystem
    VERSION 1.0.0
    DESCRIPTION "停车场管理系统 - C++ 后端"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# 统一的源文件清单：自动收集 src/ 下所有 .cpp / .h
# CONFIGURE_DEPENDS 确保增删文件后无需手动重新生成
file(GLOB PARKING_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
file(GLOB PARKING_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(parking_system ${PARKING_SOURCES} ${PARKING_HEADERS})

target_include_directories(parking_system PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# 静态链接 libgcc / libstdc++，便于在精简的运行镜像中执行
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(parking_system PRIVATE -O2 -Wall)
    target_link_options(parking_system PRIVATE -static-libgcc -static-libstdc++)
endif()

if(MSVC)
    target_compile_options(parking_system PRIVATE /W3 /utf-8)
    target_compile_definitions(parking_system PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

install(TARGETS parking_system RUNTIME DESTINATION bin)
