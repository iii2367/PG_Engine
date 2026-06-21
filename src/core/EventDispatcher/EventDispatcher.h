#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>

struct Event
{
    std::string type;
};

class EventDispatcher 
{
public:
    using DispatcherHandler = std::function<void(const Event &)>;

    void subscribe(std::string type, DispatcherHandler handler); 
    void dispatch(const Event &event);        

private:
    std::unordered_map<std::string, std::vector<DispatcherHandler>> handlers; 
};

#endif
