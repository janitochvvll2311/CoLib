#ifndef COLIB_ANCHOR_LAYOUT_HPP
#define COLIB_ANCHOR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API AnchorLayout
        : public Block,
          public virtual Layout
    {

    public:
        Anchor getHorizontalAnchor(const SharedWidget &widget) const;
        void setHorizontalAnchor(const SharedWidget &widget, Anchor value);

        Anchor getVerticalAnchor(const SharedWidget &widget) const;
        void setVerticalAnchor(const SharedWidget &widget, Anchor value);

        //////////////////////////////////////////////////////////////////////////

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        ///////////////////////////////////////////////////////////////////////////

        bool dispatchEvent(Widget *target, const sf::Event &event) override;
        bool bubbleEvent(Widget *target, const sf::Event &event) override;

        AnchorLayout();
        virtual ~AnchorLayout();

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
            Anchor getHorizontalAnchor() const;
            void setHorizontalAnchor(Anchor value);

            Anchor getVerticalAnchor() const;
            void setVerticalAnchor(Anchor value);

            WidgetHolder();
            virtual ~WidgetHolder();

        private:
            Anchor m_hAnchor;
            Anchor m_vAnchor;
        };

        //////////////////////////////////////////////////////

        SharedHolder getHolder(const SharedWidget &widget) const;

        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_ANCHOR_LAYOUT_HPP