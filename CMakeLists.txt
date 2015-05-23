project(CppExercises CXX)
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
set(MAIN_SRCS
    main.cpp
)
add_subdirectory(src)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -std=c++11 -O0 -g")
add_executable(${PROJECT_NAME} ${MAIN_SRCS})

target_link_libraries(${PROJECT_NAME} mystd)
