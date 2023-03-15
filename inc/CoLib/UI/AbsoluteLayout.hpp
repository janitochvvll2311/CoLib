#ifndef COLIB_ABSOLUTE_LAYOUT_HPP
#define COLIB_ABSOLUTE_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API AbsoluteLayout
        : public Block,
          public virtual Layout
    {

    public:
        enum Side
        {
            Left,
            Top,
            Right,
            Bottom
        };

        Anchor getAnchor(const SharedWidget &widget) const;
        void setAnchor(const SharedWidget &widget, Anchor value);

        Side getSide(const SharedWidget &widget) const;
        void setSide(const SharedWidget &widget, Side value);

        f32t getPosition(const SharedWidget &widget) const;
        void setPosition(const SharedWidget &widget, f32t value);

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        ///////////////////////////////////////////////////////////////////////////

        bool dispatchEvent(Widget *target, const sf::Event &event) override;

        AbsoluteLayout();
        virtual ~AbsoluteLayout();

    protected:
        sf::Vector2f getContentSize() const override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        class WidgetHolder;
        using SharedHolder = std::shared_ptr<WidgetHolder>;

        /////////////////////////////////////////////////////////////

        class WidgetHolder : public co::WidgetHolder
        {
        public:
            Anchor getAnchor() const;
            void setAnchor(Anchor value);

            Side getSide() const;
            void setSide(Side value);

            f32t getPosition() const;
            void setPosition(f32t value);

            WidgetHolder();
            virtual ~WidgetHolder();

        private:
            Anchor m_anchor;
            Side m_side;
            f32t m_position;
        };

        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_ABSOLUTE_LAYOUT_HPP