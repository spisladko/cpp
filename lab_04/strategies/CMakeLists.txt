project(strategies)

set(SOURCES
        computer1.cpp
        computer2.cpp
        computer_interface.cpp
        human.cpp)
set(HEADERS
        computer1.h
        computer2.h
        computer_interface.h
        human.h
        interface.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
