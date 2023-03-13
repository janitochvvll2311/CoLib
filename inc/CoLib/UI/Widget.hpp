#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/UI/Box.hpp>

namespace co
{

    class Aligner;
    class Layout;

    ///////////////////////////////////////

    class COLIB_UI_API Widget
        : public Box,
          public virtual sf::Drawable
    {

        friend Layout;

    public:
        virtual bool isValid() const;
        virtual void invalidate();

        virtual void compact();
        virtual void inflate(const sf::Vector2f &size, const Aligner *const aligner = nullptr);
        void update(bool force = false) const;

        Widget();
        virtual ~Widget();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        virtual void onUpdate() const;

    private:
        mutable bool m_isValid;
        Layout* m_parent;
    };

}

#endif // COLIB_WIDGET_HPP