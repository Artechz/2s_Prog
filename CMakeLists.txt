cmake_minimum_required(VERSION 3.15)
project(ProgPractice2 C)

set(CMAKE_C_STANDART 11)
set(ALLEGRO_DIR "C:\\MinGW")
include_directories(${ALLEGRO_DIR}/include)
link_directories(${ALLEGRO_DIR}/lib)

add_executable(ProgPractice2 main.c LS_Allegro.c LS_Allegro.h my_allegro_ui.c my_allegro_ui.h my_files.c my_files.h my_race_basic.h my_race_basic.c my_sortedlist.c my_sortedlist.h)

target_link_libraries(ProgPractice2 -lmingw32 -lallegro-5.0.10-monolith-md-debug)