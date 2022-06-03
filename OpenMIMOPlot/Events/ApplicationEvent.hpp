#ifndef APPLICATION_EVENT_HPP
#define APPLICATION_EVENT_HPP

#include "Event.hpp"

namespace OpenMIMO
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent();
        ~WindowCloseEvent() = default;
    };

    class WindowMinimizeEvent : public Event
    {
    public:
        WindowMinimizeEvent();
        ~WindowMinimizeEvent() = default;
    };

    class WindowRestoreEvent : public Event
    {
    public:
        WindowRestoreEvent();
        ~WindowRestoreEvent() = default;
    };

    class WindowResizeEvent : public Event
    {
    public:
        virtual std::any GetEventData() const override;

        WindowResizeEvent(uint32_t width, uint32_t height);
        ~WindowResizeEvent() = default;
    
    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };

    class FramebufferResizeEvent : public Event
    {
    public:
        virtual std::any GetEventData() const override;

        FramebufferResizeEvent(uint32_t width, uint32_t height);
        ~FramebufferResizeEvent() = default;
    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };
}

#endif
