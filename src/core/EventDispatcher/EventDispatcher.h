#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType // Перечислення наших івентів для підписки на них
{
  PG_Mouse_Move,
  // PG_Mouse_Click,
  PG_LMouse_Click,
  PG_RMouse_Click,
  PG_Key_Down_W,
  PG_Key_Up_W,
  PG_Key_Down_A,
  PG_Key_Up_A,
  PG_Key_Down_S,
  PG_Key_Up_S,
  PG_Key_Down_D,
  PG_Key_Up_D,
  PG_Key_Down_Q,
  PG_Key_Up_Q,
  PG_Key_Down_E,
  PG_Key_Up_E,
  PG_Key_Down_Z,
  PG_Key_Up_Z,
  PG_Key_Down_X,
  PG_Key_Up_X,
  PG_Key_Down_C,
  PG_Key_Up_C,
  PG_Key_Down_F,
  PG_Key_Up_F,
  PG_Key_Down_R,
  PG_Key_Up_R,
  PG_Key_Down_V,
  PG_Key_Up_V,
  PG_Key_Down_B,
  PG_Key_Up_B,
  PG_Key_Down_G,
  PG_Key_Up_G,
  PG_Key_Down_H,
  PG_Key_Up_H,
  PG_Key_Down_I,
  PG_Key_Up_I,
  PG_Key_Down_J,
  PG_Key_Up_J,
  PG_Key_Down_K,
  PG_Key_Up_K,
  PG_Key_Down_L,
  PG_Key_Up_L,
  PG_Key_Down_M,
  PG_Key_Up_M,
  PG_Key_Down_N,
  PG_Key_Up_N,
  PG_Key_Down_O,
  PG_Key_Up_O,
  PG_Key_Down_P,
  PG_Key_Up_P,
  PG_Key_Down_T,
  PG_Key_Up_T,
  PG_Key_Down_U,
  PG_Key_Up_U,
  PG_Key_Down_Y,
  PG_Key_Up_Y,
  PG_Key_Down_SPACE,
  PG_Key_Up_SPACE,
  PG_Key_Down_LCTRL,
  PG_Key_Up_LCTRL,
  PG_Key_Down_LSHIFT,
  PG_Key_Up_LSHIFT,
  PG_Key_Down_ENTER,
  PG_Key_Up_ENTER,
  PG_Key_Down_TAB,
  PG_Key_Up_TAB,
  PG_Key_Down_ESC,
  PG_Key_Up_ESC,
  PG_Key_Down_1,
  PG_Key_Up_1,
  PG_Key_Down_2,
  PG_Key_Up_2,
  PG_Key_Down_3,
  PG_Key_Up_3,
  PG_Key_Down_4,
  PG_Key_Up_4,
  PG_Key_Down_5,
  PG_Key_Up_5,
  PG_Key_Down_6,
  PG_Key_Up_6,
  PG_Key_Down_7,
  PG_Key_Up_7,
  PG_Key_Down_8,
  PG_Key_Up_8,
  PG_Key_Down_9,
  PG_Key_Up_9,
  PG_Key_Down_0,
  PG_Key_Up_0,
};

struct Event // Структура інформації про івент
{
  EventType type;
  int keyCode = 0;
  float x = 0;
  float y = 0;
};

class EventDispatcher {
public:
  using DispatcherHandler =
      std::function<void(const Event &)>; // Сигнатура функції івенту

  void subscribe(EventType type,
                 DispatcherHandler handler); // підписка на івент
  void dispatch(const Event &event);         // запуск всіх функцій з івенту

private:
  std::unordered_map<EventType, std::vector<DispatcherHandler>>
      handlers; // Сховище функцій івентів
};

#endif
