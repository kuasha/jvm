cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(hmjvm VERSION 1.0)

add_executable(hmjvm kjvm.cpp JavaClass.cpp ClassHeap.cpp ExecutionEngine.cpp ObjectHeap.cpp NativeMethods.cpp opcodes.cpp FilePathManager.cpp)
