# Vole Machine Simulator — Bonus GUI (Dear ImGui + SDL2 + OpenGL)
#
# Build:
#   mkdir build && cd build
#   cmake ..
#   make
#   ./vole_gui
#
# Requirements: SDL2 and OpenGL development files (already present on this machine).
# The backend source files are compiled as-is; no backend logic is changed.

cmake_minimum_required(VERSION 3.10)
project(VoleSimGUI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find cross-platform dependencies
find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

# Vole machine backend sources (unchanged core logic)
set(VOLE_BACKEND_SRCS
    ALU.cpp
    CPU.cpp
    machine.cpp
    Memory.cpp
    Register.cpp
    RegisterFile.cpp
    Screen.cpp
    Programs.cpp
    InstructionDecoder.cpp
    Instruction.cpp
)

# Dear ImGui (vendored under vendor/imgui/)
set(IMGUI_SRCS
    vendor/imgui/imgui.cpp
    vendor/imgui/imgui_demo.cpp
    vendor/imgui/imgui_draw.cpp
    vendor/imgui/imgui_tables.cpp
    vendor/imgui/imgui_widgets.cpp
    vendor/imgui/backends/imgui_impl_sdl2.cpp
    vendor/imgui/backends/imgui_impl_opengl3.cpp
)

# GUI entry point (frontend only)
set(GUI_SRCS gui_main.cpp)

add_executable(vole_gui
    ${VOLE_BACKEND_SRCS}
    ${IMGUI_SRCS}
    ${GUI_SRCS}
)

target_include_directories(vole_gui PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends
    ${SDL2_INCLUDE_DIRS}
    ${OPENGL_INCLUDE_DIR}
)

target_link_libraries(vole_gui PRIVATE
    SDL2::SDL2
    OpenGL::GL
)

# Nice output name & location
set_target_properties(vole_gui PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
