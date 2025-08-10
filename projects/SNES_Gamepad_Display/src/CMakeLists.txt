# CMakeList.txt : CMake project for GamePad_SDL_CMake_Test, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable(GamePad_SDL_CMake_Test "GamePad_SDL_CMake_Test.cpp" "GamePad_SDL_CMake_Test.h")

# Find packages from vcpkg
find_package(SDL3 CONFIG REQUIRED)

# Link libraries (raylib_cpp is now available from FetchContent)
target_link_libraries(GamePad_SDL_CMake_Test PRIVATE SDL3::SDL3 raylib raylib_cpp)

# The images for the controller and stuff
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/images 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR})