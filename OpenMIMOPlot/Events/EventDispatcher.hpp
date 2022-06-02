#ifndef EVENT_DISPATCHER_HPP
#define EVENT_DISPATCHER_HPP

#include "Event.hpp"

#include <unordered_map>
#include <functional>
#include <list>

namespace OpenMIMO
{
    struct FunctionStarter
    {
        std::function<void(Event&)> Function;
        EventType Code;

        FunctionStarter(const std::function<void(Event&)>& functionValue, EventType code) :
            Function(functionValue), Code(code)
        {}
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(const std::list<FunctionStarter>& functionStarter);
        ~EventDispatcher() = default;
        
        const std::function<void(Event&)>& GetDispatchFunction(const EventType eventType);
    private:
        std::unordered_map<EventType, std::function<void(Event &)>> m_EventActions;
    };   
}

#endif
