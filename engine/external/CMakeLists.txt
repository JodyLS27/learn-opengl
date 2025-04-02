# GLAD File

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(
  glad STATIC
  glad/src/glad.c
  glad/include/glad/glad.h
  glad/include/KHR/khrplatform.h
)

target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)