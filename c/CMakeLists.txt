cmake_minimum_required(VERSION 3.7)
project(Perso C)

set(CMAKE_C_STANDARD 11)

add_executable(Perso main.c filmotheque.h filmotheque.c film.h film.c realisateur.c realisateur.h listChrono.h listChrono.c)
