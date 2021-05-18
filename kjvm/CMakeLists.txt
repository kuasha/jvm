cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(hmjvm VERSION 0.1)

add_executable(hmjvm kjvm.cpp JavaClass.cpp ClassHeap.cpp ExecutionEngine.cpp ObjectHeap.cpp NativeMethods.cpp opcodes.cpp FilePathManager.cpp)

add_executable(hmjvmtest tests/test.cpp JavaClass.cpp ClassHeap.cpp ExecutionEngine.cpp ObjectHeap.cpp NativeMethods.cpp opcodes.cpp FilePathManager.cpp)
target_include_directories(hmjvmtest PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
)
