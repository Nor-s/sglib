add_executable(01_HelloWorld ./main.cpp)

target_link_libraries(01_HelloWorld  sglib)
target_include_directories(01_HelloWorld  PUBLIC ./)