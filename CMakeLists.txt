cmake_minimum_required(VERSION 3.10)
project(CUT)

set(CMAKE_BUILD_TYPE Debug)

set(LIB
    src/analyzer.c
    src/printer.c
    src/reader.c
)
add_library(${PROJECT_NAME}-lib STATIC ${LIB})

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)
find_package (Threads REQUIRED)

set(COMPILE_FLAGS PRIVATE -pthread -Wall -Wextra -Werror)

add_compile_options(${PROJECT_NAME} ${COMPILE_FLAGS})
target_compile_options(${PROJECT_NAME} ${COMPILE_FLAGS})
target_compile_options(${PROJECT_NAME}-lib ${COMPILE_FLAGS})

target_link_libraries(${PROJECT_NAME} Threads::Threads)