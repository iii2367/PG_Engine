#include "SDL3InputPlatform.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
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
    case SDL_EVENT_MOUSE_BUTTON_DOWN: {

      getMousePosition(e.x, e.y);
      switch (event.button.button) {
      case SDL_BUTTON_LEFT: {
        e.type = EventType::PG_LMouse_Click;
        dispatcher.dispatch(e);
        break;
      }
      case SDL_BUTTON_RIGHT: {
        e.type = EventType::PG_RMouse_Click;
        dispatcher.dispatch(e);
        break;
      }
      }
      break;
    }
    case SDL_EVENT_KEY_DOWN: // Наш івент якщо кнопка натистута
    {
      // key.mod нужно отдельно потому что дефайн имеет тот же код
      // + к этому эти кнопки могут использоваться в комбинациях

      getMousePosition(e.x, e.y);
      if (event.key.mod & SDL_KMOD_LCTRL) {
        e.type = EventType::PG_Key_Down_LCTRL;
        dispatcher.dispatch(e);
      }
      if (event.key.mod & SDL_KMOD_LSHIFT) {
        e.type = EventType::PG_Key_Down_LSHFT;
        dispatcher.dispatch(e);
      }
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
      case SDLK_Q: {
        e.type = EventType::PG_Key_Down_Q;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_E: {
        e.type = EventType::PG_Key_Down_E;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_Z: {
        e.type = EventType::PG_Key_Down_Z;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_X: {
        e.type = EventType::PG_Key_Down_X;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_C: {
        e.type = EventType::PG_Key_Down_C;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_F: {
        e.type = EventType::PG_Key_Down_F;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_R: {
        e.type = EventType::PG_Key_Down_R;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_V: {
        e.type = EventType::PG_Key_Down_V;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_SPACE: {
        e.type = EventType::PG_Key_Down_SPC;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_RETURN: {
        e.type = EventType::PG_Key_Down_ENTR;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_TAB: {
        e.type = EventType::PG_Key_Down_TAB;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_ESCAPE: {
        e.type = EventType::PG_Key_Down_ESC;
        dispatcher.dispatch(e);
        break;
      }
      }
      break;
    case SDL_EVENT_MOUSE_MOTION:
      getMousePosition(e.x, e.y);
      e.type = EventType::PG_Mouse_Move;
      dispatcher.dispatch(e);
      break;
    }
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
