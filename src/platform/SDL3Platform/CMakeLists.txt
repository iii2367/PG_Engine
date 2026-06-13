project(SDL3Platform)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

add_library(SDL3Platform SHARED 
    SDL3Platform.cpp
    SDL3BasePlatform/SDL3BasePlatform.cpp
    SDL3WindowPlatform/SDL3WindowPlatform.cpp
    SDL3InputPlatform/SDL3InputPlatform.cpp
    #SDL3AudioPlatform/SDL3AudioPlatform.cpp
)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(SDL3Platform PUBLIC SDL3::SDL3)

#target_link_libraries(SDL3Platform PRIVATE SDL3::SDL3)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_command(TARGET SDL3Platform POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/bin
)
