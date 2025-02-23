add_executable(_template_ ./main.cpp)

target_link_libraries(_template_  sglib benchmark::benchmark)
target_include_directories(_template_  PUBLIC ./)