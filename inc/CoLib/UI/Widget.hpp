#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/UI/Box.hpp>

namespace sf
{
    class Event;
}

namespace co
{

    class Layout;

    ///////////////////////////////////////

    class COLIB_UI_API Widget
        : public Box,
          public virtual sf::Drawable
    {

        friend Layout;

    public:
        virtual f32t getOuterWidth() const;
        virtual f32t getInnerWidth() const;

        virtual f32t getOuterHeight() const;
        virtual f32t getInnerHeight() const;

        ///////////////////////////////////////////////

        virtual bool isValid() const;
        virtual void invalidate();

        virtual void compact();
        virtual void inflate(const sf::Vector2f &size);
        void update(bool force = false) const;

        ////////////////////////////////////////////////////////

        virtual bool handleEvent(const sf::Event &event);

        Widget(const Widget &other) = delete;

        Widget();
        virtual ~Widget();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        virtual void onUpdate() const;

    private:
        mutable bool m_isValid;
        Layout *m_parent;
    };

}

#endif // COLIB_WIDGET_HPP