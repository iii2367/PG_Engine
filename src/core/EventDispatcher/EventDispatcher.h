#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType // Перечислення наших івентів для підписки на них
{
  PG_Mouse_Move,
  PG_Mouse_Click,
  PG_Key_Down_W,
  PG_Key_Up_W,
  PG_Key_Down_A,
  PG_Key_Up_A,
  PG_Key_Down_S,
  PG_Key_Up_S,
  PG_Key_Down_D,
  PG_Key_Up_D
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
