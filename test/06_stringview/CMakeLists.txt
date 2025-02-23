add_executable(06_stringview ./main.cpp)

target_link_libraries(06_stringview  sglib benchmark::benchmark)
target_include_directories(06_stringview  PUBLIC ./)
