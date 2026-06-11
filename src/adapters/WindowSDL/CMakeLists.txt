project(WindowSDL)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/WindowSDL")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/WindowSDL") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/WindowSDL")

add_library(WindowSDL SHARED 
    WindowSDL.cpp
)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(WindowSDL PRIVATE SDL3::SDL3)

add_definitions(-DUNICODE -D_UNICODE)

