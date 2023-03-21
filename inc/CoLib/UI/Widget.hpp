#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Box.hpp>

namespace co
{

    class Box;

    //////////////////////////////////////////////////////////////

    class COLIB_UI_API Widget
        : public Box,
          public virtual sf::Drawable,
          public virtual Node
    {

    public:
        bool isValid() const;
        void invalidate();
        void update(bool force = false) const;

        virtual void compact();
        virtual void inflate(const sf::Vector2f &size);

        Widget();
        virtual ~Widget();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual void onUpdate() const;
        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;

    private:
        mutable bool m_isValid;
    };

}

#endif // COLIB_WIDGET_HPP