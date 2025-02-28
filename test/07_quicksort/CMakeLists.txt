add_executable(07_quicksort ./main.cpp)

target_link_libraries(07_quicksort  sglib benchmark::benchmark)
target_include_directories(07_quicksort  PUBLIC ./)
