#ifndef COLIB_BACKGROUND_HPP
#define COLIB_BACKGROUND_HPP

#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Background
        : public Widget
    {

    public:
        Graph &getGraph();
        const Graph &getGraph() const;

        Background();
        virtual ~Background();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable Graph m_graph;
    };

}

#endif // COLIB_BACKGROUND_HPP