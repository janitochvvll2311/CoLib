#ifndef COLIB_GRAPH_HPP
#define COLIB_GRAPH_HPP

#include <memory>
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

    using SharedTexture = std::shared_ptr<sf::Texture>;

    ////////////////////////////////////////////////////

    class COLIB_GRAPHICS_API Graph
        : public sf::Transformable,
          public virtual sf::Drawable
    {

    public:
        sf::PrimitiveType getPrimitiveType() const;
        void setPrimitiveType(sf::PrimitiveType type);

        const sf::VertexArray &getVertexes() const;
        void setPoints(const PointSource &source, szt precision = 1);

        const sf::Color &getColor() const;
        void setColor(const sf::Color &color);

        const sf::FloatRect &getTextureRect() const;
        void setTextureRect(const sf::FloatRect &texRect);

        const SharedTexture &getTexture() const;
        void setTexture(const SharedTexture &texture, bool reset = true);

        void fitPoints(const sf::FloatRect &bounds);

        Graph();
        ~Graph();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

    private:
        sf::VertexArray m_array;
        sf::Color m_color;
        sf::FloatRect m_texRect;
        SharedTexture m_texture;
    };

}

#endif // COLIB_GRAPH_HPP