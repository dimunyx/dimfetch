cmake_minimum_required(VERSION 3.25)
project(dimfetch VERSION 0.5.0 LANGUAGES CXX)

set(DIMFETCH_VERSION "${PROJECT_VERSION}" CACHE STRING "Version printed by dimfetch")

file(GLOB DIMFETCH_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/modules/*.cpp"
)

add_executable(dimfetch ${DIMFETCH_SOURCES})
target_include_directories(dimfetch PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_compile_features(dimfetch PRIVATE cxx_std_26)
target_compile_definitions(dimfetch PRIVATE DIMFETCH_VERSION="${DIMFETCH_VERSION}")

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(dimfetch PRIVATE -Wall -Wextra -Wno-ignored-attributes)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(dimfetch PRIVATE -O3 -pipe)
    endif()
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(dimfetch PRIVATE -flto=thin)
    target_link_options(dimfetch PRIVATE -flto=thin)
endif()
