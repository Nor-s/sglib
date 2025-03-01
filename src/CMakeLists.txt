set(SGLIB_SRC
    sglib.cpp

    ./Commons/Logger.cpp

    ./Timer/Timer.cpp

    ./Algorithm/Random.cpp
    ./Algorithm/Sort.cpp

    ./Data/TestData.cpp
)

add_library(sglib STATIC ${SGLIB_SRC})

target_link_libraries(sglib PUBLIC spdlog)
target_include_directories(sglib  PUBLIC 
    ${CMAKE_HOME_DIRECTORY}/external/** 
    ${CMAKE_HOME_DIRECTORY}/include/**)
