project(ppm2pgm_pbm)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -w")

set(GLOBAL_SOURCES main.c readPPM.c saveImg.c utils.c)

add_executable(2pgm ${GLOBAL_SOURCES} convert2PGM.c)
add_executable(2pbm ${GLOBAL_SOURCES} convert2PBM.c)

