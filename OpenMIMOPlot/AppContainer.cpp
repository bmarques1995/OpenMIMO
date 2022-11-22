#include "AppContainer.hpp"
#include "PlotLayers/TestLayer.hpp"
#include "PlotLayers/BodeLayer.hpp"
#include "PlotLayers/RootLocusLayer.hpp"

OpenMIMO::AppContainer::AppContainer() :
    Application()
{
    TransferFunction<double> plant({ 1 }, {1, 15, 59, 45});
    PushLayer(new TestLayer());
    PushLayer(new BodeLayer());
    PushLayer(new RootLocusLayer(plant));
}

OpenMIMO::AppContainer::~AppContainer()
{

}
