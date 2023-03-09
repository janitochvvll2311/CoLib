#include <CoLib/UI/GraphBackground.hpp>

namespace co
{

    void GraphBackground::setBounds(const sf::FloatRect &bounds)
    {
        fitPoints(bounds);
    }

    GraphBackground::GraphBackground() {}
    GraphBackground::~GraphBackground() {}

}