set(SGLIB_SRC
    sglib.cpp
    ./Timer/Timer.cpp
)

add_library(sglib STATIC ${SGLIB_SRC})

# target_link_libraries(sglib sglib)
target_include_directories(sglib  PUBLIC ../include)
