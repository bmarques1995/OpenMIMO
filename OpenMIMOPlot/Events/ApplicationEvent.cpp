#include "ApplicationEvent.hpp"
#include <sstream>

OpenMIMO::WindowCloseEvent::WindowCloseEvent() :
    Event(EventType::WindowCloseEvent, "Window will be closed")
{

}

OpenMIMO::WindowMinimizeEvent::WindowMinimizeEvent() :
    Event(EventType::WindowMinimizeEvent, "Window minimized")
{

}

OpenMIMO::WindowRestoreEvent::WindowRestoreEvent() :
    Event(EventType::WindowRestoreEvent, "Window minimized")
{

}

OpenMIMO::WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) :
    m_Width(width), m_Height(height), Event(EventType::WindowResizeEvent)
{
    std::stringstream message;
    message << "New window size (" << m_Width << "," << m_Height << ")";
    m_EventInfo = message.str();
}
        
const uint32_t OpenMIMO::WindowResizeEvent::GetWidth() const
{
    return m_Width;
}

const uint32_t OpenMIMO::WindowResizeEvent::GetHeight() const
{
    return m_Height;
}

OpenMIMO::FramebufferResizeEvent::FramebufferResizeEvent(uint32_t width, uint32_t height) :
    m_Width(width), m_Height(height), Event(EventType::FramebufferResizeEvent)
{
    std::stringstream message;
    message << "New window size (" << m_Width << "," << m_Height << ")";
    m_EventInfo = message.str();
}
        
const uint32_t OpenMIMO::FramebufferResizeEvent::GetWidth() const
{
    return m_Width;
}

const uint32_t OpenMIMO::FramebufferResizeEvent::GetHeight() const
{
    return m_Height;
}

//OpenMIMO::FramebufferResizeEvent::WindowResizeEvent