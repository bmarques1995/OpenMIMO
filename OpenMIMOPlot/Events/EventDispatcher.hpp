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
        std::function<void(const Event&)> Function;
        EventType Code;

        FunctionStarter(const std::function<void(const Event&)>& functionValue, EventType code) :
            Function(functionValue), Code(code)
        {}
    };

    class EventDispatcher
    {
    public:
        EventDispatcher(const std::list<FunctionStarter>& functionStarter);
        ~EventDispatcher() = default;
        
        void Dispatch(const Event& e);
    private:
        std::unordered_map<EventType, std::function<void(const Event &)>> m_EventActions;
    };   
}

#endif
