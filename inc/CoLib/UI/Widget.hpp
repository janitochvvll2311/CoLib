#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Export.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>

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

        /////////////////////////////////////////////////

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        /////////////////////////////////////////////////

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        virtual f32t getHorizontalSpacing() const;
        virtual f32t getVerticalSpacing() const;

        Gravity getHorizontalGravity() const;
        void setHorizontalGravity(Gravity value);

        Gravity getVerticalGravity() const;
        void setVerticalGravity(Gravity value);

        /////////////////////////////////////////////////

        void invalidate();

        void compact();
        void inflate(const Box &box);

        Widget();
        Widget(f32t width, f32t heigth);

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        virtual void onUpdate(sf::VertexArray &array) const;

    private:
        mutable bool m_isValid;
        mutable sf::VertexArray m_array;
        sf::Color m_color;

        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;

        Thickness m_margin;
        Gravity m_hGravity;
        Gravity m_vGravity;
    };

}

#endif // COLIB_WIDGET_HPP