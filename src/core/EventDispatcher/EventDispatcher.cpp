#include "EventDispatcher.h"

void EventDispatcher::subscribe(EventType type, DispatcherHandler handler) // підписка на івент
{
    handlers[type].push_back(handler);
}

void EventDispatcher::dispatch(const Event& event) // запуск всіх функцій з івенту
{
    auto it = handlers.find(event.type);
    if (it != handlers.end())
    {
        for (auto& h : it->second)
        {
            h(event);
        }
    }
}
