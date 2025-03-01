add_executable(08_mergesort ./main.cpp)

target_link_libraries(08_mergesort  sglib benchmark::benchmark)
target_include_directories(08_mergesort  PUBLIC ./)
