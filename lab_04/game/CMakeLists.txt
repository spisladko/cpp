project(game)

set(SOURCES
        cell.cpp
        field.cpp
        functions.cpp
        game.cpp
        step.cpp)
set(HEADERS
        cell.h
        field.h
        functions.h
        game.h
        step.h)

include_directories(../)

add_library(game ${SOURCES} ${HEADERS})
