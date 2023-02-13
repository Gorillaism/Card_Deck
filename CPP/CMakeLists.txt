cmake_minimum_required(VERSION 3.11)
project(Assignment_1_1 VERSION 0.1.0)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

# include(CTest)
# enable_testing()
#add_subdirectory(tests)

include_directories(include)


set(SOURCES main.cpp deck.cpp)
add_executable(deck ${SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


include(FetchContent)
#FetchContent_Declare(
#  googletest
#  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
#)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.13.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)

set(TEST_SOURCES test_deck.cpp deck.cpp)

add_executable(
    test_deck
    ${TEST_SOURCES}
)

target_link_libraries(
    test_deck
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_deck)
