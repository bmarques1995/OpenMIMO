#ifndef GLFW_CONTROLLER_HPP
#define GLFW_CONTROLLER_HPP

#include "InterfaceGraphicsAPI/WindowController.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>
#include <string>

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"

class GLFWController : public WindowController
{
    friend class GL4Context;
private:
    GraphicsContext* m_Context;

    GLFWwindow* m_Window;
    
    uint32_t m_Width;
    uint32_t m_Height;
    std::string m_Title;

public:
    GLFWController(const WindowProps& props = WindowProps());
    ~GLFWController();

    virtual bool ShouldClose() const override;

    virtual uint32_t GetWidth() const override;
    virtual uint32_t GetHeight() const override;

    virtual std::any GetNativeWindow() const override;

    virtual void Update() override;

    virtual void Present() override;
};

#endif