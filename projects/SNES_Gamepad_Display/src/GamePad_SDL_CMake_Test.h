#pragma once

#include <raylib.h>
#include "raylib-cpp.hpp"
#include <chrono>
#include <thread>
#include <print>

namespace GamepadConstants
{
    constexpr int INITIAL_WINDOW_WIDTH = 1280;
    constexpr int INITIAL_WINDOW_HEIGHT = 720;
    constexpr int TARGET_FPS = 60;
    constexpr int STABILITY_THRESHOLD = 5;
    constexpr int MIN_FONT_SIZE = 10;
    constexpr int DEFAULT_FONT_SIZE = 35;
    constexpr int TEXT_OFFSET = 50;
    constexpr auto GAMEPAD_INIT_DELAY = std::chrono::milliseconds(500);
}

struct GamepadTextures
{
    // Textures are public data members
    raylib::Texture2D unpressed;
    raylib::Texture2D pressedA;
    raylib::Texture2D pressedB;
    raylib::Texture2D pressedX;
    raylib::Texture2D pressedY;
    raylib::Texture2D pressedUp;
    raylib::Texture2D pressedLeft;
    raylib::Texture2D pressedDown;
    raylib::Texture2D pressedRight;
    raylib::Texture2D pressedStart;
    raylib::Texture2D pressedSelect;
    raylib::Texture2D pressedLBump;
    raylib::Texture2D pressedRBump;

    // Textures get loaded up in constructor
    GamepadTextures()
        : unpressed("images/controller.png")
        , pressedA("images/pressed-png/A.png")
        , pressedB("images/pressed-png/B.png")
        , pressedX("images/pressed-png/X.png")
        , pressedY("images/pressed-png/Y.png")
        , pressedUp("images/pressed-png/up.png")
        , pressedLeft("images/pressed-png/left.png")
        , pressedDown("images/pressed-png/down.png")
        , pressedRight("images/pressed-png/right.png")
        , pressedStart("images/pressed-png/start.png")
        , pressedSelect("images/pressed-png/select.png")
        , pressedLBump("images/pressed-png/L-bumper.png")
        , pressedRBump("images/pressed-png/R-bumper.png")
    {
    }
};

struct ScalingInfo
{
    float scale;
    float offsetX;
    float offsetY;

    ScalingInfo(int currentWidth, int currentHeight, int originalWidth, int originalHeight)
    {
        float scaleX = static_cast<float>(currentWidth) / originalWidth;
        float scaleY = static_cast<float>(currentHeight) / originalHeight;
        scale = std::min(scaleX, scaleY);
        offsetX = (currentWidth - (originalWidth * scale)) / 2.0f;
        offsetY = (currentHeight - (originalHeight * scale)) / 2.0f;
    }
};

class GamepadDisplay
{
private:
    GamepadTextures textures;
    bool gamepadWasConnected = false;
    int stabilityCounter = 0;

public:
    const GamepadTextures& getTextures() const { return textures; }

    bool updateGamepadConnection(bool currentlyAvailable)
    {
        if (currentlyAvailable == gamepadWasConnected)
        {
            stabilityCounter = 0;
        }
        else
        {
            ++stabilityCounter;
            if (stabilityCounter >= GamepadConstants::STABILITY_THRESHOLD)
            {
                gamepadWasConnected = currentlyAvailable;
                stabilityCounter = 0;
            }
        }
        return gamepadWasConnected;
    }

    void drawGamepadButtons(const raylib::Gamepad& gamepad, const ScalingInfo& scaling)
    {
        const raylib::Vector2 position{ scaling.offsetX, scaling.offsetY };

        // This lambda function is called below
        auto drawButtonIfPressed = [&](auto condition, const raylib::Texture2D& texture)
        {
            if (condition)
            {
                texture.Draw(position, 0.0f, scaling.scale, raylib::WHITE);
            }
        };

        // Face buttons (A, B, X, Y)
        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_RIGHT_FACE_DOWN) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(7)),
            textures.pressedA
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(6)),
            textures.pressedB
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_RIGHT_FACE_UP) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(5)),
            textures.pressedY
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_RIGHT_FACE_LEFT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(8)),
            textures.pressedX
        );

        // D-pad buttons
        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_LEFT_FACE_UP) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(1)),
            textures.pressedUp
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_LEFT_FACE_LEFT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(4)),
            textures.pressedLeft
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_LEFT_FACE_DOWN) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(3)),
            textures.pressedDown
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_LEFT_FACE_RIGHT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(2)),
            textures.pressedRight
        );

        // Start/Select buttons
        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_MIDDLE_RIGHT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(15)),
            textures.pressedStart
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_MIDDLE_LEFT) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(13)),
            textures.pressedSelect
        );

        // Shoulder buttons
        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_LEFT_TRIGGER_1) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(11)),
            textures.pressedLBump
        );

        drawButtonIfPressed(
            gamepad.IsButtonDown(GAMEPAD_BUTTON_RIGHT_TRIGGER_2) ||
            gamepad.IsButtonDown(static_cast<GamepadButton>(12)),
            textures.pressedRBump
        );
    }

    void drawNoGamepadMessage(const ScalingInfo& scaling)
    {
        int fontSize = std::max(
            static_cast<int>(GamepadConstants::DEFAULT_FONT_SIZE * scaling.scale),
            GamepadConstants::MIN_FONT_SIZE
        );

        raylib::DrawText(
            "No Gamepad Connected",
            static_cast<int>(GamepadConstants::TEXT_OFFSET * scaling.scale + scaling.offsetX),
            static_cast<int>(GamepadConstants::TEXT_OFFSET * scaling.scale + scaling.offsetY),
            fontSize,
            raylib::Color(raylib::GRAY)
        );
    }
};
