#ifndef COLIB_GRAPH_BACKGROUND_HPP
#define COLIB_GRAPH_BACKGROUND_HPP

#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Export.hpp>
#include <CoLib/UI/Background.hpp>

namespace co
{

    class COLIB_UI_API GraphBackground
        : public Graph,
          public virtual Background
    {
    public:
        void setBounds(const sf::FloatRect &bounds) override final;

        GraphBackground();
        ~GraphBackground();
    };

}

#endif // COLIB_GRAPH_BACKGROUND_HPP