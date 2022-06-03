#include "ApplicationEvent.hpp"
#include <sstream>
#include <utility>

OpenMIMO::WindowCloseEvent::WindowCloseEvent() :
    Event(EventType::WindowCloseEvent, "Window will be closed")
{

}

OpenMIMO::WindowMinimizeEvent::WindowMinimizeEvent() :
    Event(EventType::WindowMinimizeEvent, "Window minimized")
{

}

OpenMIMO::WindowRestoreEvent::WindowRestoreEvent() :
    Event(EventType::WindowRestoreEvent, "Window restored")
{

}

OpenMIMO::WindowResizeEvent::WindowResizeEvent(uint32_t width, uint32_t height) :
    m_Width(width), m_Height(height), Event(EventType::WindowResizeEvent)
{
    std::stringstream message;
    message << "New window size (" << m_Width << "," << m_Height << ")";
    m_EventInfo = message.str();
}

std::any OpenMIMO::WindowResizeEvent::GetEventData() const
{
    return std::pair<uint32_t, uint32_t>(m_Width, m_Height);
}

OpenMIMO::FramebufferResizeEvent::FramebufferResizeEvent(uint32_t width, uint32_t height) :
    m_Width(width), m_Height(height), Event(EventType::FramebufferResizeEvent)
{
    std::stringstream message;
    message << "New framebuffer size (" << m_Width << "," << m_Height << ")";
    m_EventInfo = message.str();
}

std::any OpenMIMO::FramebufferResizeEvent::GetEventData() const
{
    return std::pair<uint32_t, uint32_t>(m_Width, m_Height);
}
