#include "GamePad_SDL_CMake_Test.h"

int main() 
{
    using namespace GamepadConstants;

    // Window setup
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    raylib::Window window(INITIAL_WINDOW_WIDTH, INITIAL_WINDOW_HEIGHT, "SNES Gamepad Display");
    window.SetTargetFPS(TARGET_FPS);

    std::this_thread::sleep_for(GAMEPAD_INIT_DELAY);

    GamepadDisplay display;

    while (!window.ShouldClose()) 
    {
        window.BeginDrawing();
        window.ClearBackground(raylib::BLACK);

        ScalingInfo scaling(
            window.GetWidth(),
            window.GetHeight(),
            INITIAL_WINDOW_WIDTH,
            INITIAL_WINDOW_HEIGHT
        );

        // Always draw base controller
        display.getTextures().unpressed.Draw(
            raylib::Vector2{ scaling.offsetX, scaling.offsetY },
            0.0f,
            scaling.scale,
            raylib::WHITE
        );

        // Handle gamepad input
        bool connected = display.updateGamepadConnection(raylib::Gamepad::IsAvailable(0));

        if (connected) 
        {
            raylib::Gamepad gamepad(0);
            display.drawGamepadButtons(gamepad, scaling);
        }
        else 
        {
            display.drawNoGamepadMessage(scaling);
        }

        window.EndDrawing();
    }

    return 0;
}