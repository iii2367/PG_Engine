#include "SDL3InputPlatform.h"

#include <SDL3/SDL.h>

bool SDL3InputPlatform::pollEvents(EventDispatcher& dispatcher)
{
    // Обробка івентів покищо тільки закриття вікна пізніше реалізуємо підписку подій
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        Event e{};
        switch (event.type)
        {
            case SDL_EVENT_QUIT: { return false; }
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



