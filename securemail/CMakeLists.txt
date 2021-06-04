cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(securemail VERSION 0.1)

add_subdirectory(third_party/tink)

add_executable(securemail securemail.cpp)

target_link_libraries(securemail tink::static)
