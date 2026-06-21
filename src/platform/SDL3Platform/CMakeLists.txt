project(SDL3Platform)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

add_library(SDL3Platform SHARED 
    SDL3Platform.cpp
    SDL3WindowPlatform/SDL3WindowPlatform.cpp
    SDL3InputPlatform/SDL3InputPlatform.cpp
    SDL3AudioPlatform/SDL3AudioPlatform.cpp
)

find_package(SDL3 REQUIRED CONFIG)
find_package(SDL3_mixer REQUIRED CONFIG)

#target_link_libraries(SDL3Platform PUBLIC SDL3::SDL3)

target_link_libraries(SDL3Platform PRIVATE SDL3::SDL3 SDL3_mixer::SDL3_mixer)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_command(TARGET SDL3Platform POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/bin
)
add_custom_command(TARGET SDL3Platform POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3_mixer::SDL3_mixer>
    ${CMAKE_BINARY_DIR}/bin
)
