#ifndef COLIB_GRAPH_HPP
#define COLIB_GRAPH_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/Graphics/Export.hpp>

namespace sf
{
    class Texture;
}

namespace co
{

    class PointSource;

    ////////////////////////////////////////////////////

    class COLIB_GRAPHICS_API Graph
        : public sf::Transformable,
          public sf::Drawable
    {

    public:
        void setPrimitiveType(sf::PrimitiveType type);
        void setPoints(const PointSource &source, szt precision = 1);
        void setColor(const sf::Color &color);
        void setTextureRect(const sf::FloatRect &texRect);
        void setTexture(const sf::Texture *const texture);
        void fitPoints(const sf::FloatRect& bounds);

        Graph();
        ~Graph();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

    private:
        sf::VertexArray m_array;
        sf::Color m_color;
        const sf::Texture *m_texture;
    };

}

#endif // COLIB_GRAPH_HPP