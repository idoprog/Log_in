cmake_minimum_required(VERSION 3.14)
project(Log_in C)

set(CMAKE_C_STANDARD 99)
add_executable(Log_in main.c low_ui_funcs.c low_ui_funcs.h high_ui_funcs.c high_ui_funcs.h help_funcs.c help_funcs.h)
target_link_libraries(Log_in pthread)
target_link_libraries(Log_in ncurses)