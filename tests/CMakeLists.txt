set(CMAKE_CXX_FLAGS "-I${CMAKE_SOURCE_DIR}/include")
add_executable(rv32 hello.cpp)
target_link_libraries(rv32 riscv)