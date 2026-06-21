#include "EventDispatcher.h"

void EventDispatcher::subscribe(std::string type, DispatcherHandler handler)
{
    handlers[type].push_back(handler);
}

void EventDispatcher::dispatch(const Event& event)
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
