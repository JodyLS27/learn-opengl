# Engine CMake Lists

# Used mark this as a static library
add_library(engine STATIC)

target_include_directories(engine PRIVATE include)

# Additional CMake scripts, Add External Libraries 
include(cmake/FetchGLFW.cmake)

# Glad files
add_subdirectory(external)

add_subdirectory(src)

# glfw files
target_link_libraries(engine PRIVATE glad glfw) # Might need to be Pulic if the editor includes headers from engine.