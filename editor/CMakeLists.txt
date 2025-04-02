# editor CMake lists

add_executable(editor src/editor.cpp)
target_include_directories(editor PRIVATE 
${CMAKE_SOURCE_DIR}/editor/include
${CMAKE_SOURCE_DIR}/engine/include
)

target_link_libraries(editor PRIVATE engine)