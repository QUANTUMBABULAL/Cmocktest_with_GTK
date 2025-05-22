cmake_minimum_required(VERSION 3.10)
project(QuestionGeneratorApp C)

set(CMAKE_C_STANDARD 11)

# Find GTK
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# Add source files
add_executable(QuestionGeneratorApp
    src/main.c
    src/file_utils.c
    src/generator.c
    src/quiz.c
    src/style.c
)

# Link GTK
target_link_libraries(QuestionGeneratorApp ${GTK3_LIBRARIES})
