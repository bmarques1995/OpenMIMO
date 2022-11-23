#include "EventDispatcher.hpp"

OpenMIMO::EventDispatcher::EventDispatcher(const std::list<OpenMIMO::FunctionStarter>& functionStarter)
{
    for (auto &i : functionStarter)
        m_EventActions[i.Code] = i.Function;
}
        
void OpenMIMO::EventDispatcher::Dispatch(const Event& e)
{
    m_EventActions[e.GetEventType()](e);
}
