#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Export.hpp>
#include <CoLib/UI/Box.hpp>

namespace co
{

    class COLIB_UI_API Widget
        : public sf::Transformable,
          public sf::Drawable,
          public Box
    {

    public:
        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        void invalidate();

        Widget(f32t width = 0, f32t heigth = 0);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        virtual void onUpdate(sf::VertexArray &array) const;

    private:
        mutable bool m_isValid;
        mutable sf::VertexArray m_array;

        sf::Color m_color;
    };

}

#endif // COLIB_WIDGET_HPP