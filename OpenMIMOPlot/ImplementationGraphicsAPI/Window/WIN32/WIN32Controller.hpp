#ifndef WIN32_CONTROLLER_HPP
#define WIN32_CONTROLLER_HPP

#include "InterfaceGraphicsAPI/WindowController.hpp"

#include <cstdio>
#include <string>

class WIN32Controller : public WindowController
{
private:
    //GLFWwindow* m_Window;
    uint32_t m_Width;
    uint32_t m_Height;
    std::string m_Title;
public:
    WIN32Controller(const WindowProps& props = WindowProps());
    ~WIN32Controller();

    virtual bool ShouldClose() const override;

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    virtual std::any GetNativeWindow() const override;

    virtual void Update() override;

    virtual void Present() override;
};

#endif