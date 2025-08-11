# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project("GamePad_SDL_CMake_Test")

# Set C++23 standard globally for modern C++ practices
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include FetchContent module
include(FetchContent)

# Configure raylib build options BEFORE declaring it
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)          # Don't build examples
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)             # Don't build games
set(SUPPORT_MODULE_RSHAPES ON CACHE BOOL "" FORCE)   # Basic shapes (needed for gamepad display)
set(SUPPORT_MODULE_RTEXTURES ON CACHE BOOL "" FORCE) # Texture support
set(SUPPORT_MODULE_RTEXT ON CACHE BOOL "" FORCE)     # Text rendering
set(SUPPORT_MODULE_RMODELS OFF CACHE BOOL "" FORCE)  # 3D models (not needed)
set(SUPPORT_MODULE_RAUDIO ON CACHE BOOL "" FORCE)    # Audio support

# Most importantly - disable file format loaders that depend on nanosvg
set(SUPPORT_FILEFORMAT_SVG OFF CACHE BOOL "" FORCE)  # This disables nanosvg dependency

# Fetch raylib
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)

# Fetch raylib-cpp
FetchContent_Declare(
    raylib_cpp
    GIT_REPOSITORY https://github.com/RobLoach/raylib-cpp.git
    GIT_TAG v5.0.1
)

# Make both available to all subprojects
FetchContent_MakeAvailable(raylib raylib_cpp)

# Include sub-projects.
add_subdirectory("GamePad_SDL_CMake_Test")
