#ifndef GRAPHICS_CONTEXT_HPP
#define GRAPHICS_CONTEXT_HPP

#include <any>
#include <cstdint>

namespace OpenMIMO {
    class GraphicsContext
    {
    private:
        /* data */
        /*
        std::string_view m_GLSLVersion = "#version 130";
        const WindowController* m_WindowController;
        float m_ClearColor[4] = {.0f,.0f,.0f,1.0f};*/
    public:
        //GraphicsContext(const WindowController* windowController);
        //~GraphicsContext();
        virtual void Update() = 0;
        virtual void SetClearColor(float x, float y, float z, float w = 1.0f) = 0;
        virtual void Present() = 0;
        virtual void SetViewport(uint32_t width, uint32_t height) = 0;
        virtual std::any GetComponentConstructor() const = 0;
    };
}

#endif
