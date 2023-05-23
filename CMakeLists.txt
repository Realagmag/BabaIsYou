cmake_minimum_required(VERSION 3.22.1)

project(BabaIsYou)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} sfml-graphics)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

add_library(BabaIsYouLib
  src/Board.cpp
  src/Game.cpp
  src/Game.h
  src/Window.h
  src/Window.cpp
  src/ObjectOnField.cpp
  src/SolidObject.cpp
  src/SolidObjects/Baba.cpp
  src/SolidObjects/Wall.cpp
  src/SolidObjects/Flag.cpp
  src/SolidObjects/Rock.cpp
  src/SolidObjects/Lava.cpp
  src/SolidObjects/Water.cpp
  src/SolidObjects/Skull.cpp
  src/SolidObjects/Rock.cpp
  src/SolidObjects/Tree.cpp
  src/paths.h)

target_link_libraries(BabaIsYouLib PRIVATE
sfml-system sfml-window sfml-graphics sfml-network sfml-audio
)

target_include_directories(BabaIsYouLib PUBLIC "${PROJECT_BINARY_DIR}")
target_link_libraries(${PROJECT_NAME} BabaIsYouLib)

########## Tests ##########

find_package(Catch2 REQUIRED)

add_executable(test
tests/board_tests.cpp
tests/solid_object_tests.cpp
tests/baba_tests.cpp)

target_link_libraries(test PRIVATE Catch2::Catch2WithMain BabaIsYouLib)
