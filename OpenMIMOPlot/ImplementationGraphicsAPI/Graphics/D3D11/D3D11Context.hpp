#ifndef D3D11_CONTEXT_HPP
#define D3D11_CONTEXT_HPP

#include "InterfaceGraphicsAPI/GraphicsContext.hpp"
#include "InterfaceGraphicsAPI/WindowController.hpp"

#include <string>
#include <GLSafeInclude.hpp>

class D3D11Context : public GraphicsContext
{
private:
    //const WindowController* m_WindowController;
    //float m_ClearColor[4] = {.0f,.0f,.0f,1.0f};
public:
    D3D11Context();
    ~D3D11Context();

    virtual void Update() override;
    virtual void SetClearColor(float x, float y, float z, float w) override;
    virtual std::any GetComponentConstructor() const override;
    virtual void Present() override;
};

#endif
