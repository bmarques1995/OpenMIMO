#ifndef GL4_CONTEXT_HPP
#define GL4_CONTEXT_HPP

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"

#include <string>
#include <GLSafeInclude.hpp>
#include <GLFW/glfw3.h>

namespace OpenMIMO
{
    class GL4Context : public GraphicsContext
    {
    private:
        std::string_view m_GLSLVersion = "#version 130";
        GLFWwindow* m_Window;
        float m_ClearColor[4] = { .0f,.0f,.0f,1.0f };
    public:
        GL4Context(GLFWwindow* window);
        ~GL4Context();

        virtual void Update() override;
        virtual void SetViewport(uint32_t width, uint32_t height) override;
        virtual void SetClearColor(float x, float y, float z, float w) override;
        virtual std::any GetComponentConstructor() const override;
        virtual void Present() override;
    };
}

#endif
