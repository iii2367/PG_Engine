project(GFXSDL3Adapter)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

add_library(GFXSDL3Adapter SHARED 
    GFXSDL3Adapter.cpp
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_image REQUIRED CONFIG)

target_link_libraries(GFXSDL3Adapter PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)

target_include_directories(GFXSDL3Adapter PRIVATE
    ../../../lib/glm
)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_command(TARGET GFXSDL3Adapter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/bin
)
