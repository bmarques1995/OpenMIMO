#include "Layer.hpp"

Layer::Layer(std::string_view layerName) :
    m_LayerName(layerName)
{

}

Layer::~Layer()
{

}

std::string_view Layer::GetName() const
{
    return m_LayerName;
}