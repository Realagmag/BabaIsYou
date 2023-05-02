cmake_minimum_required(VERSION 3.22.1)

project(BabaIsYou)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} sfml-graphics)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)