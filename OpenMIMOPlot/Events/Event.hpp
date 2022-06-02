#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>

namespace OpenMIMO
{
    enum class EventType
    {
        None = 0,

        WindowCloseEvent,
        WindowMinimizeEvent,
        WindowRestoreEvent,
        WindowResizeEvent,
        FramebufferResizeEvent
    };

    class Event
    {
    public:
        EventType GetEventType() const;
        const std::string& GetEventInfo() const;
    protected:
        Event(EventType eventType, const std::string& eventInfo = "Generic Event");
        ~Event() = default;

        std::string m_EventInfo;
        EventType m_EventType;
    };
}

#endif
