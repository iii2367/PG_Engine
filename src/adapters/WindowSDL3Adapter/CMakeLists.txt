project(WindowSDL3Adapter)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

add_library(WindowSDL3Adapter SHARED 
    WindowSDL3Adapter.cpp
)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(WindowSDL3Adapter PRIVATE SDL3::SDL3)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_command(TARGET WindowSDL3Adapter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/bin
)
