#ifndef COLIB_SURFACE_HPP
#define COLIB_SURFACE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Surface
        : public Widget,
          public virtual LeafNode
    {

    public:
        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        Surface();
        virtual ~Surface();

    protected:
        void onUpdate() const override;
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        mutable sf::VertexArray m_array;
        sf::Color m_color;
    };

}

#endif // COLIB_SURFACE_HPP