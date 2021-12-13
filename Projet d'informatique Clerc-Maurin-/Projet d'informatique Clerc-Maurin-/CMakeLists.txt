project(quoridor C)

set(CMAKE_C_STANDARD 99)

add_executable(quoridor game.c game.h display.c display.h input.c input.h tool.c tool.h)
