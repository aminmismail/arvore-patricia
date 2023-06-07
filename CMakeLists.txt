cmake_minimum_required(VERSION 3.21)
project(arvore-patricia C)

set(CMAKE_C_STANDARD 11)

add_executable(arvore-patricia main.c arquivo.c patricia.c)
