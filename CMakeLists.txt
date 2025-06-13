cmake_minimum_required(VERSION 3.9)
project(GOOD LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_FLAGS_DEBUG "-g -lm -O0")
set(CMAKE_CXX_FLAGS_DEBUG "-g")


file( GLOB_RECURSE  impl_c "impl/*.c")
file(GLOB_RECURSE impl_cpp "impl/*.cpp")
file(GLOB_RECURSE malloc "alloc/*c")
file(GLOB_RECURSE src_c "src/*.c")
file(GLOB_RECURSE src_cpp  "src/*.cpp")


add_library(malloc_l SHARED ${malloc})
add_library(lib_impl SHARED ${impl_c} ${impl_cpp})
target_link_libraries(lib_impl m)
target_include_directories(malloc_l PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(lib_impl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(malloc_l m)
target_link_libraries(lib_impl malloc_l)

add_executable(exe ${src_c} ${src_cpp})
target_include_directories(exe PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(exe PUBLIC lib_impl)
