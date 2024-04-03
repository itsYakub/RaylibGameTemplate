cmake_minimum_required(VERSION 3.14) # FetchContent is available in 3.11+
project(game VERSION 1.0)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

# Our Project

set(
    SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set(
    INCLUDE_DIRECTORIES
    -I${CMAKE_SOURCE_DIR}/lib/raylib/src # raysan5/raylib
    -I${CMAKE_SOURCE_DIR}/lib/json/single_include/nlohmann # nlohmann/json
    -I${CMAKE_SOURCE_DIR}/lib/emsdk/upstream/emscripten/system/include # emscripten-core/emsdk
)

add_executable(${PROJECT_NAME} ${SOURCES})
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set(
        CMAKE_EXE_LINKER_FLAGS 
        "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s WASM=1 -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 -Os -Wall -Wextra --shell-file ${CMAKE_SOURCE_DIR}/lib/raylib/src/minshell.html"
    )

    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()