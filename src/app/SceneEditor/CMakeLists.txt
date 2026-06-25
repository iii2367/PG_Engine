project(SceneEditor)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin") 
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/lib")

add_executable(SceneEditor
    main.cpp
    ../../core/EventDispatcher/EventDispatcher.cpp
    ../../core/ActionManager/ActionManager.cpp
    ../../../lib/ImGuiSDL3/backend/imgui_impl_sdl3.cpp
    ../../../lib/ImGuiSDL3/backend/imgui_impl_sdlrenderer3.cpp
    ../../../lib/ImGuiSDL3/src/imgui.cpp
    ../../../lib/ImGuiSDL3/src/imgui_demo.cpp
    ../../../lib/ImGuiSDL3/src/imgui_draw.cpp
    ../../../lib/ImGuiSDL3/src/imgui_tables.cpp
    ../../../lib/ImGuiSDL3/src/imgui_widgets.cpp
    ../SceneEditor/ImGui/imguiInterface.cpp 
    ../../core/GameRender/RenderSystem.cpp
    #тут всі cpp
)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(SceneEditor PRIVATE SDL3::SDL3) # тут якщо є лінковочні бібліотеки то просто через пробіл після SDL3

target_include_directories(SceneEditor PRIVATE
    #тут пиши шлях до заголовків бібліотеки щоб можна було підключати <> а не повним шляхом ""
    ../../../lib/glm
    ../../../lib/ImGuiSDL3/backend
    ../../../lib/ImGuiSDL3/src
    ../../utils
)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_command(TARGET SceneEditor POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    $<TARGET_FILE:SDL3::SDL3>
    ${CMAKE_BINARY_DIR}/bin
)




