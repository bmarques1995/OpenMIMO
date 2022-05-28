#include "Layer.hpp"

OpenMIMO::Layer::Layer(std::string_view layerName) :
    m_LayerName(layerName)
{

}

OpenMIMO::Layer::~Layer()
{

}

std::string_view OpenMIMO::Layer::GetName() const
{
    return m_LayerName;
}