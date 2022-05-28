#include "AppContainer.hpp"
#include "PlotLayers/TestLayer.hpp"

OpenMIMO::AppContainer::AppContainer() :
    Application()
{
    PushLayer(new TestLayer());
}

OpenMIMO::AppContainer::~AppContainer()
{

}
