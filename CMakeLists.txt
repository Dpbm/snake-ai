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

add_executable(snake main.cpp)
target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIRS})

add_executable(manual manual_tests.cpp)

add_subdirectory(helpers)
add_subdirectory(game)
add_subdirectory(genetic)
add_subdirectory(matrix)
add_subdirectory(machine)
add_subdirectory(nativefiledialog)

file(GLOB HELPERS_FILES "helpers/*.cpp")
add_library(helpers ${HELPERS_FILES})
target_link_libraries(helpers matrix machine)

file(GLOB GENETIC_FILES "genetic/*.cpp")
add_library(genetic ${GENETIC_FILES})
target_link_libraries(genetic players matrix machine board helpers)

file(GLOB MATRIX_FILES "matrix/*.cpp")
add_library(matrix ${MATRIX_FILES})

file(GLOB MACHINE_FILES "machine/*.cpp")
add_library(machine ${MACHINE_FILES})
target_link_libraries(machine helpers matrix)

file(GLOB BOARD_FILE "game/board.cpp")
file(GLOB SCREENS_FILES "game/screens/*.cpp")
file(GLOB PLAYERS_FILES "game/players/*.cpp")
add_library(board ${BOARD_FILE})
add_library(screens ${SCREENS_FILES})
add_library(players ${PLAYERS_FILES})
target_link_libraries(players machine matrix genetic helpers ${SDL2_LIBRARIES})
target_link_libraries(screens players board helpers genetic ${SDL2_LIBRARIES} SDL2_ttf nativefiledialog)
target_link_libraries(board helpers players)

target_link_libraries(snake PRIVATE helpers board screens players ${SDL2_LIBRARIES} SDL2_ttf)
target_link_libraries(manual PRIVATE helpers board players)

enable_testing()

file(GLOB TESTS "tests/*_test.cc")
add_executable(tests ${TESTS})
target_link_libraries(tests matrix helpers genetic players board machine GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(tests)
