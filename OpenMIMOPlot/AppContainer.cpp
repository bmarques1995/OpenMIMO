#include "AppContainer.hpp"
#include "PlotLayers/TestLayer.hpp"
#include "PlotLayers/BodeLayer.hpp"
#include "PlotLayers/RootLocusLayer.hpp"
#include "Utils/Clock.hpp"
#include "Utils/Console.hpp"

OpenMIMO::AppContainer::AppContainer() :
    Application()
{
    Clock clock;
    TransferFunction<double> plant({ 1 }, {1, 15, 59, 45});
    TransferFunction<double> bodePlant({ 1 }, {1, 6, 5});
    //PushLayer(new TestLayer());
    clock.Start();
    PushLayer(new BodeLayer(bodePlant));
    auto bodeEnd = clock.GetEllapsedTime();
    clock.Start();
    PushLayer(new RootLocusLayer(plant));
    auto rLocusEnd = clock.GetEllapsedTime();
    ConsoleWrapper::Debug("Root Locus Time: {0}, Bode Time: {1}", rLocusEnd, bodeEnd);
}

OpenMIMO::AppContainer::~AppContainer()
{

}
