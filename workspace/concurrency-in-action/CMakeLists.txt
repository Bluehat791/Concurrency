cmake_minimum_required(VERSION 3.25.1)
project(templates1)
set(CMAKE_CXX_STANDARD 23)

set(MEMORY_SANITIZER_FLAGS "-fsanitize=memory -fno-omit-frame-pointer -g")

function(add_sanitizer TARGET)
  if(ENABLE_MEMORY_SANITIZER)
    target_compile_options(${TARGET} PRIVATE ${MEMORY_SANITIZER_FLAGS})
    target_link_libraries(${TARGET} PRIVATE -lrt) # Только для GCC, может не потребоваться для Clang
  endif()
endfunction()

add_executable(${PROJECT_NAME} main.cpp)
add_sanitizer(${PROJECT_NAME})