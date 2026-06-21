#include "SDL3InputPlatform.h"
#include "../../../core/Key/KeyId.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_scancode.h>
#include <any>

void SDL3InputPlatform::setKeyId(InputKey& key)
{
    if (key.type == DeviceType::Keyboard)
    {
        switch (key.keyId)
        {
            case KeyId::A: key.platformId = SDL_SCANCODE_A; break;
            case KeyId::B: key.platformId = SDL_SCANCODE_B; break;
            case KeyId::C: key.platformId = SDL_SCANCODE_C; break;
            case KeyId::D: key.platformId = SDL_SCANCODE_D; break;
            case KeyId::E: key.platformId = SDL_SCANCODE_E; break;
            case KeyId::F: key.platformId = SDL_SCANCODE_F; break;
            case KeyId::G: key.platformId = SDL_SCANCODE_G; break;
            case KeyId::H: key.platformId = SDL_SCANCODE_H; break;
            case KeyId::I: key.platformId = SDL_SCANCODE_I; break;
            case KeyId::J: key.platformId = SDL_SCANCODE_J; break;
            case KeyId::K: key.platformId = SDL_SCANCODE_K; break;
            case KeyId::L: key.platformId = SDL_SCANCODE_L; break;
            case KeyId::M: key.platformId = SDL_SCANCODE_M; break;
            case KeyId::N: key.platformId = SDL_SCANCODE_N; break;
            case KeyId::O: key.platformId = SDL_SCANCODE_O; break;
            case KeyId::P: key.platformId = SDL_SCANCODE_P; break;
            case KeyId::Q: key.platformId = SDL_SCANCODE_Q; break;
            case KeyId::R: key.platformId = SDL_SCANCODE_R; break;
            case KeyId::S: key.platformId = SDL_SCANCODE_S; break;
            case KeyId::T: key.platformId = SDL_SCANCODE_T; break;
            case KeyId::U: key.platformId = SDL_SCANCODE_U; break;
            case KeyId::V: key.platformId = SDL_SCANCODE_V; break;
            case KeyId::W: key.platformId = SDL_SCANCODE_W; break;
            case KeyId::X: key.platformId = SDL_SCANCODE_X; break;
            case KeyId::Y: key.platformId = SDL_SCANCODE_Y; break;
            case KeyId::Z: key.platformId = SDL_SCANCODE_Z; break;

            case KeyId::Digit0: key.platformId = SDL_SCANCODE_0; break;
            case KeyId::Digit1: key.platformId = SDL_SCANCODE_1; break;
            case KeyId::Digit2: key.platformId = SDL_SCANCODE_2; break;
            case KeyId::Digit3: key.platformId = SDL_SCANCODE_3; break;
            case KeyId::Digit4: key.platformId = SDL_SCANCODE_4; break;
            case KeyId::Digit5: key.platformId = SDL_SCANCODE_5; break;
            case KeyId::Digit6: key.platformId = SDL_SCANCODE_6; break;
            case KeyId::Digit7: key.platformId = SDL_SCANCODE_7; break;
            case KeyId::Digit8: key.platformId = SDL_SCANCODE_8; break;
            case KeyId::Digit9: key.platformId = SDL_SCANCODE_9; break;

            case KeyId::Enter: key.platformId = SDL_SCANCODE_RETURN; break;
            case KeyId::Space: key.platformId = SDL_SCANCODE_SPACE; break;
            case KeyId::Escape: key.platformId = SDL_SCANCODE_ESCAPE; break;
            case KeyId::Tab: key.platformId = SDL_SCANCODE_TAB; break;
            case KeyId::Backspace: key.platformId = SDL_SCANCODE_BACKSPACE; break;

            case KeyId::ArrowUp: key.platformId = SDL_SCANCODE_UP; break;
            case KeyId::ArrowDown: key.platformId = SDL_SCANCODE_DOWN; break;
            case KeyId::ArrowLeft: key.platformId = SDL_SCANCODE_LEFT; break;
            case KeyId::ArrowRight: key.platformId = SDL_SCANCODE_RIGHT; break;

            case KeyId::ShiftLeft: key.platformId = SDL_SCANCODE_LSHIFT; break;
            case KeyId::ShiftRight: key.platformId = SDL_SCANCODE_RSHIFT; break;
            case KeyId::ControlLeft: key.platformId = SDL_SCANCODE_LCTRL; break;
            case KeyId::ControlRight: key.platformId = SDL_SCANCODE_RCTRL; break;
            case KeyId::AltLeft: key.platformId = SDL_SCANCODE_LALT; break;
            case KeyId::AltRight: key.platformId = SDL_SCANCODE_RALT; break;

            case KeyId::CapsLock: key.platformId = SDL_SCANCODE_CAPSLOCK; break;
            case KeyId::NumLock: key.platformId = SDL_SCANCODE_NUMLOCKCLEAR; break;
            case KeyId::ScrollLock: key.platformId = SDL_SCANCODE_SCROLLLOCK; break;

            default: key.platformId = SDL_SCANCODE_UNKNOWN; break;
        }
    }
    else if (key.type == DeviceType::Mouse)
    {
        switch (key.keyId)
        {
            case KeyId::MouseLeft: key.platformId = SDL_BUTTON_LMASK; break;
            case KeyId::MouseRight: key.platformId = SDL_BUTTON_RMASK; break;
            case KeyId::MouseMiddle: key.platformId = SDL_BUTTON_MMASK; break;
            case KeyId::MouseBack: key.platformId = SDL_BUTTON_X1MASK; break;
            case KeyId::MouseForward: key.platformId = SDL_BUTTON_X2MASK; break;

            default: key.platformId = 0; break;
        }
    }
}

bool SDL3InputPlatform::getKeyState(const InputKey& key)
{
    switch (key.type) 
    {
        case DeviceType::Keyboard:
        {
            auto state = SDL_GetKeyboardState(nullptr);
            return state[std::any_cast<SDL_Scancode>(key.platformId)];
        }
        case DeviceType::Mouse:
        {
            auto mouse = SDL_GetMouseState(nullptr, nullptr);
            return (mouse & std::any_cast<Uint32>(key.platformId)) != 0;
        }
    }
    return false;
}

bool SDL3InputPlatform::pollEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type)
        { 
            case SDL_EVENT_QUIT: { return false; } 
        }
    }
    return true;
}

void SDL3InputPlatform::getMousePosition(float &x, float &y)
{
    SDL_GetMouseState(&x, &y);
}
