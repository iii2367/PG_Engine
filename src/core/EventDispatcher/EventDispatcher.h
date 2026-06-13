#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <vector>

enum class EventType // Перечислення наших івентів для підписки на них
{
    KeyDown,
    KeyUp,
    MouseMove,
    MouseClick 
};

struct Event // Структура інформації про івент
{ 
    EventType type;
    int keyCode = 0;
    int x = 0;
    int y = 0;
};

class EventDispatcher
{
public:
    using Handler = std::function<void(const Event&)>; // Сигнатура функції івенту
    
    void subscribe(EventType type, Handler handler); // підписка на івент
    void dispatch(const Event& event); // запуск всіх функцій з івенту

private:
    std::unordered_map<EventType, std::vector<Handler>> handlers; // Сховище функцій івентів
};

#endif
