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
        WindowResizeEvent(uint32_t width, uint32_t height);
        ~WindowResizeEvent() = default;

        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
    
    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };

    class FramebufferResizeEvent : public Event
    {
    public:
        
        FramebufferResizeEvent(uint32_t width, uint32_t height);
        ~FramebufferResizeEvent() = default;

        const uint32_t GetWidth() const;
        const uint32_t GetHeight() const;
    
    private:
        uint32_t m_Width;
        uint32_t m_Height;
    };
}

#endif
