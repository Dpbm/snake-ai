cmake_minimum_required(VERSION 3.20.4)
project(genetic_snake VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(SDL2 REQUIRED)

add_executable(ga.out main.cpp)

target_include_directories(ga.out PRIVATE ${SDL2_INCLUDE_DIRS})

add_subdirectory(helpers)
add_subdirectory(game)
add_subdirectory(genetic)

file(GLOB HELPERS_FILES "helpers/*.cpp")
add_library(helpers ${HELPERS_FILES})

file(GLOB GAME_FILES "game/*.cpp")
add_library(game ${GAME_FILES})
target_link_libraries(game helpers)

file(GLOB GENETIC_FILES "genetic/*.cpp")
add_library(genetic ${GENETIC_FILES})
target_link_libraries(genetic helpers)

target_link_libraries(ga.out PRIVATE helpers game genetic ${SDL2_LIBRARIES})

