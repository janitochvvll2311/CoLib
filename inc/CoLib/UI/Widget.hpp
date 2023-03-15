#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <functional>
#include <memory>
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

    class Widget;
    using SharedWidget = std::shared_ptr<Widget>;

    ///////////////////////////////////////

    class COLIB_UI_API Widget
        : public Box,
          public virtual sf::Drawable
    {

        friend Layout;

    public:
        using EventListener = std::function<void(Widget &, const sf::Event &)>;

        virtual f32t getOuterWidth() const;
        virtual f32t getInnerWidth() const;

        virtual f32t getOuterHeight() const;
        virtual f32t getInnerHeight() const;

        ///////////////////////////////////////////////

        bool isValid() const;
        void invalidate();

        virtual void compact();
        virtual void inflate(const sf::Vector2f &size);
        void update(bool force = false) const;

        //////////////////////////////////////////////////////////////////

        virtual sf::Vector2f getInnerPoint(const sf::Vector2f &point) const;

        virtual bool dispatchEvent(Widget *target, const sf::Event &event);
        virtual bool bubbleEvent(Widget *target, const sf::Event &event);
        virtual bool handleEvent(Widget *target, const sf::Event &event);

        Widget(const Widget &other) = delete;

        Widget();
        virtual ~Widget();

    protected:
        bool dispatchInnerEvent(const SharedWidget &widget, Widget *target, const sf::Event &event) const;
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        virtual void onUpdate() const;

    private:
        mutable bool m_isValid;
        Layout *m_parent;
    };

}

#endif // COLIB_WIDGET_HPP