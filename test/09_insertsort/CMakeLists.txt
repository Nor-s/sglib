add_executable(09_insertsort ./main.cpp)

target_link_libraries(09_insertsort  sglib benchmark::benchmark)
target_include_directories(09_insertsort  PUBLIC ./)
