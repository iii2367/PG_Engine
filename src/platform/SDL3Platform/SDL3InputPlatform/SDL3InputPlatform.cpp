#include "SDL3InputPlatform.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>

bool SDL3InputPlatform::pollEvents(EventDispatcher& dispatcher)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        Event e{};
        switch (event.type)
        {
            case SDL_EVENT_QUIT: { return false; }
            case SDL_EVENT_KEY_DOWN: // Наш івент якщо кнопка натистута
            {
                e.type = EventType::KeyDown; // Ми перекладаємо івент на наш 
                dispatcher.dispatch(e);  // і запускаємо обробку події якщо є підписка то вона спрацює
            }
        }
    }
    return true;
}

bool SDL3InputPlatform::isKeyPressed(int keyCode)
{
    // Для виловленя коду кнопок покищо невірна сигнатура потім підправимо
}

bool SDL3InputPlatform::isMouseButtonPressed(int button)
{
    // Диловлення кнопок миші теж поки невірно
}

void SDL3InputPlatform::getMousePosition(int& x, int& y)
{
    // Отримання кординат миші
}



