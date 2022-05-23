#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"
#include "InterfaceGraphicsAPI/WindowController.hpp"

#include <string>
#include <glad/gl.h>

class GL4Context : public GraphicsContext
{
private:
    std::string_view m_GLSLVersion = "#version 130";
    const WindowController* m_WindowController;
    float m_ClearColor[4] = {.0f,.0f,.0f,1.0f};
public:
    GL4Context(const WindowController* windowController);
    ~GL4Context();

    virtual void Update() override;
    virtual void SetClearColor(float x, float y, float z, float w) override;
    virtual std::any GetComponentConstructor() const override;
};

#endif
