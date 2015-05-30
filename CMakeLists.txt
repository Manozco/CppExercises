project(CppExercises CXX)
cmake_minimum_required(VERSION 2.8)
#aux_source_directory(. SRC_LIST)
set(MAIN_SRCS
    main.cpp
)
add_subdirectory(src)
set(COMMON_FLAGS "-Wall -Wextra -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${COMMON_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${COMMON_FLAGS} -O0 -g")
add_executable(${PROJECT_NAME} ${MAIN_SRCS})

target_link_libraries(${PROJECT_NAME} mystd)
