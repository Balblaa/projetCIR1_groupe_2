cmake_minimum_required(VERSION 3.7)
project(c C)

set(CMAKE_C_STANDARD 11)

add_executable(c main.c filmotheque.h filmotheque.c film.h film.c realisateur.c realisateur.h listChrono.h listChrono.c)
