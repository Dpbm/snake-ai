cmake_minimum_required(VERSION 3.20.4)
project(genetic_snake VERSION 0.1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_MAIN)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

find_package(SDL2 REQUIRED)

add_executable(ga.out ${TARGET_MAIN})

target_include_directories(ga.out PRIVATE ${SDL2_INCLUDE_DIRS})

add_subdirectory(helpers)
add_subdirectory(game)
add_subdirectory(genetic)
add_subdirectory(matrix)
add_subdirectory(machine)

file(GLOB HELPERS_FILES "helpers/*.cpp")
add_library(helpers ${HELPERS_FILES})
target_link_libraries(helpers genetic machine matrix ${SDL2_LIBRARIES})

file(GLOB GENETIC_FILES "genetic/*.cpp")
add_library(genetic ${GENETIC_FILES})
target_link_libraries(genetic helpers)

file(GLOB MATRIX_FILES "matrix/*.cpp")
add_library(matrix ${MATRIX_FILES})
target_link_libraries(matrix helpers genetic)

file(GLOB MACHINE_FILES "machine/*.cpp")
add_library(machine ${MACHINE_FILES})
target_link_libraries(machine helpers matrix genetic)

file(GLOB GAME_FILES "game/*.cpp")
file(GLOB SCREENS_FILES "game/screens/*.cpp")
add_library(game ${GAME_FILES})
add_library(screens ${SCREENS_FILES})
target_link_libraries(screens genetic game machine matrix helpers ${SDL2_LIBRARIES} SDL2_ttf)
target_link_libraries(game helpers screens ${SDL2_LIBRARIES})


target_link_libraries(ga.out PRIVATE helpers game genetic matrix machine ${SDL2_LIBRARIES})

enable_testing()

file(GLOB TESTS "tests/*_test.cc")
add_executable(tests ${TESTS})
target_link_libraries(tests matrix helpers genetic machine ${SDL2_LIBRARIES} GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(tests)
