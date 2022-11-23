#include "Event.hpp"

OpenMIMO::Event::Event(EventType eventType, const std::string& eventInfo) :
    m_EventType(eventType), m_EventInfo(eventInfo)
{
}

OpenMIMO::EventType OpenMIMO::Event::GetEventType() const
{
    return m_EventType;
}

const std::string& OpenMIMO::Event::GetEventInfo() const
{
    return m_EventInfo;
}

std::any OpenMIMO::Event::GetEventData() const
{
    return true;
}
