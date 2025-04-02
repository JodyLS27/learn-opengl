# fetch and build the GLFW project

# Including the fetch content for SFML
include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
message(STATUS "Fetching GLFW....")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    SOURCE_DIR "${CMAKE_SOURCE_DIR}/engine/external/glfw"
)
FetchContent_MakeAvailable(glfw)

if (TARGET glfw)
  message(STATUS "glfw fetched")
else()
  message(FATAL_ERROR "Failed to fetch glfw")
endif()