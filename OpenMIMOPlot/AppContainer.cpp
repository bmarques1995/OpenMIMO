#include "AppContainer.hpp"
#include "PlotLayers/TestLayer.hpp"

AppContainer::AppContainer() :
    Application()
{
    PushLayer(new TestLayer());
}

AppContainer::~AppContainer()
{

}
