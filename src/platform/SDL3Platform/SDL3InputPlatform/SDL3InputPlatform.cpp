#include "SDL3InputPlatform.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>

bool SDL3InputPlatform::pollEvents(EventDispatcher &dispatcher) {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    Event e{};
    switch (event.type) {
    case SDL_EVENT_QUIT: {
      return false;
    }
    case SDL_EVENT_KEY_DOWN: // Наш івент якщо кнопка натистута
    {
      switch (event.key.key) {

      case SDLK_W:
        e.type = EventType::PG_Key_Down_W; // Ми перекладаємо івент на наш
        dispatcher.dispatch(
            e); // і запускаємо обробку події якщо є підписка то вона спрацює
        break;
      case SDLK_A: {
        e.type = EventType::PG_Key_Down_A;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_S: {
        e.type = EventType::PG_Key_Down_S;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_D: {
        e.type = EventType::PG_Key_Down_D;
        dispatcher.dispatch(e);
        break;
      }
      }
    }
    case SDL_EVENT_MOUSE_MOTION:
      getMousePosition(e.x, e.y);
      e.type = EventType::PG_Mouse_Move;
      dispatcher.dispatch(e);
      break;
    }
  }
  return true;
}

bool SDL3InputPlatform::isKeyPressed(int keyCode) {
  // Для виловленя коду кнопок покищо невірна сигнатура потім підправимо
}

bool SDL3InputPlatform::isMouseButtonPressed(int button) {
  // Диловлення кнопок миші теж поки невірно
}

void SDL3InputPlatform::getMousePosition(float &x, float &y) {
  SDL_GetMouseState(&x, &y);
}
