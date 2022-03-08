cmake_minimum_required(VERSION 3.22.1)

project(game)

set(CMAKE_CXX_STANDARD 20)

file(GLOB SFML_SRC CONFIGURE_DEPENDS "*.h" "*.cpp" "gf/*.h" "gf/*.cpp")

add_executable(${PROJECT_NAME} ${SFML_SRC})
target_link_libraries(${PROJECT_NAME} sfml-window sfml-network sfml-system sfml-graphics sfml-audio)
