#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType // Перечислення наших івентів для підписки на них
{
  PG_Mouse_Move,
  PG_Mouse_Click,
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
  PG_Key_Down_SPC,
  PG_Key_Up_SPC,
  PG_Key_Down_LCTRL,
  PG_Key_Up_LCTRL,
  PG_Key_Down_LSHFT,
  PG_Key_Up_LSHFT,
  PG_Key_Down_ENTR,
  PG_Key_Up_ENTR,
  PG_Key_Down_TAB,
  PG_Key_Up_TAB,
  PG_Key_Down_ESC,
  PG_Key_Up_ESC,
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
  using Handler =
      std::function<void(const Event &)>; // Сигнатура функції івенту

  void subscribe(EventType type, Handler handler); // підписка на івент
  void dispatch(const Event &event); // запуск всіх функцій з івенту

private:
  std::unordered_map<EventType, std::vector<Handler>>
      handlers; // Сховище функцій івентів
};

#endif
