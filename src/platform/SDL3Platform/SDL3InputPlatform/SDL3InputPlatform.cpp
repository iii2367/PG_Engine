#include "SDL3InputPlatform.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_scancode.h>

void SDL3InputPlatform::pollState(pollStateStruct &st) {
  const bool *state = SDL_GetKeyboardState(nullptr);
  SDL_MouseButtonFlags mouseState = SDL_GetMouseState(nullptr, nullptr);
  st.w = state[SDL_SCANCODE_W];
  st.a = state[SDL_SCANCODE_A];
  st.s = state[SDL_SCANCODE_S];
  st.d = state[SDL_SCANCODE_D];
  st.q = state[SDL_SCANCODE_Q];
  st.r = state[SDL_SCANCODE_R];
  st.e = state[SDL_SCANCODE_E];
  st.f = state[SDL_SCANCODE_F];
  st.c = state[SDL_SCANCODE_C];
  st.x = state[SDL_SCANCODE_X];
  st.z = state[SDL_SCANCODE_Z];
  st.ctrl = state[SDL_SCANCODE_LCTRL];
  st.Shift = state[SDL_SCANCODE_LSHIFT];
  st.LMouseButton = (mouseState & SDL_BUTTON_LMASK);
  st.RMouseButton = (mouseState & SDL_BUTTON_RMASK);
}

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
      /*const bool *state = SDL_GetKeyboardState(nullptr);
      if (state[SDL_SCANCODE_W]) {
        e.type = EventType::PG_Key_Down_W; // Ми перекладаємо івент на наш
        dispatcher.dispatch(e);
      }
      if (state[SDL_SCANCODE_A]) {
        e.type = EventType::PG_Key_Down_A;
        dispatcher.dispatch(e);
      }
      if (state[SDL_SCANCODE_S]) {
        e.type = EventType::PG_Key_Down_S;
        dispatcher.dispatch(e);
      }
      if (state[SDL_SCANCODE_D]) {
        e.type = EventType::PG_Key_Down_D;
        dispatcher.dispatch(e);
      }
      */
      getMousePosition(e.x, e.y); /*
     if (event.key.mod & SDL_KMOD_LCTRL) {
       e.type = EventType::PG_Key_Down_LCTRL;
       dispatcher.dispatch(e);
     }
     if (event.key.mod & SDL_KMOD_LSHIFT) {
       e.type = EventType::PG_Key_Down_LSHIFT;
       dispatcher.dispatch(e);
     }*/
      switch (event.key.key) {

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
      case SDLK_B: {
        e.type = EventType::PG_Key_Down_B;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_G: {
        e.type = EventType::PG_Key_Down_G;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_H: {
        e.type = EventType::PG_Key_Down_H;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_I: {
        e.type = EventType::PG_Key_Down_I;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_J: {
        e.type = EventType::PG_Key_Down_J;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_K: {
        e.type = EventType::PG_Key_Down_K;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_L: {
        e.type = EventType::PG_Key_Down_L;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_M: {
        e.type = EventType::PG_Key_Down_M;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_N: {
        e.type = EventType::PG_Key_Down_N;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_O: {
        e.type = EventType::PG_Key_Down_O;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_P: {
        e.type = EventType::PG_Key_Down_P;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_T: {
        e.type = EventType::PG_Key_Down_T;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_U: {
        e.type = EventType::PG_Key_Down_U;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_Y: {
        e.type = EventType::PG_Key_Down_Y;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_SPACE: {
        e.type = EventType::PG_Key_Down_SPACE;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_RETURN: {
        e.type = EventType::PG_Key_Down_ENTER;
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
      case SDLK_0: {
        e.type = EventType::PG_Key_Down_0;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_1: {
        e.type = EventType::PG_Key_Down_1;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_2: {
        e.type = EventType::PG_Key_Down_2;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_3: {
        e.type = EventType::PG_Key_Down_3;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_4: {
        e.type = EventType::PG_Key_Down_4;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_5: {
        e.type = EventType::PG_Key_Down_5;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_6: {
        e.type = EventType::PG_Key_Down_6;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_7: {
        e.type = EventType::PG_Key_Down_7;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_8: {
        e.type = EventType::PG_Key_Down_8;
        dispatcher.dispatch(e);
        break;
      }
      case SDLK_9: {
        e.type = EventType::PG_Key_Down_9;
        dispatcher.dispatch(e);
        break;
      }
      case SDL_EVENT_MOUSE_MOTION: {
        getMousePosition(e.x, e.y);
        e.type = EventType::PG_Mouse_Move;
        dispatcher.dispatch(e);
        break;
      }
      }
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
