cmake_minimum_required(VERSION 3.16)
project(ParkingSystem LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

file(GLOB SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

add_executable(parking_system ${SOURCES} ${HEADERS})

target_include_directories(parking_system PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

if(UNIX AND NOT APPLE)
    target_link_libraries(parking_system PRIVATE pthread)
endif()

install(TARGETS parking_system DESTINATION bin)
