#include "WIN32Controller.hpp"

WIN32Controller::WIN32Controller(const WindowProps& props)
{
    m_Width = 0;
    m_Height = 0;
    m_Title = "";
}

WIN32Controller::~WIN32Controller()
{
    
}

bool WIN32Controller::ShouldClose() const
{
    return true;
}

uint32_t WIN32Controller::GetWidth() const
{
    return 0;
}

uint32_t WIN32Controller::GetHeight() const
{
    return 0;
}

std::any WIN32Controller::GetNativeWindow() const
{
    return nullptr;
}

void WIN32Controller::Update()
{
    
}

void WIN32Controller::Present()
{
    
}
