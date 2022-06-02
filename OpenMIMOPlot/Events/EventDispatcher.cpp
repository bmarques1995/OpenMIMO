#include "EventDispatcher.hpp"

OpenMIMO::EventDispatcher::EventDispatcher(const std::list<OpenMIMO::FunctionStarter>& functionStarter)
{
    for (auto &i : functionStarter)
        m_EventActions[i.Code] = i.Function;
}
        
const std::function<void(OpenMIMO::Event&)>& OpenMIMO::EventDispatcher::GetDispatchFunction(const EventType eventType)
{
    return m_EventActions[eventType];
}
