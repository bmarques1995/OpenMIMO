#include "ApplicationEvent.hpp"
#include <sstream>
#include <utility>

OpenMIMO::WindowCloseEvent::WindowCloseEvent() :
    Event(EventType::WindowCloseEvent, "Window will be closed")
{

}

std::any OpenMIMO::WindowMinimizeEvent::GetEventData() const
{
    return m_IsMinimized;
}

OpenMIMO::WindowMinimizeEvent::WindowMinimizeEvent(bool isMinimized) :
    Event(EventType::WindowMinimizeEvent, "Window minimized"), m_IsMinimized(isMinimized)
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
