#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class Background;
    using SharedBackground = std::shared_ptr<Background>;

    ///////////////////////////////////////////////////////

    class COLIB_UI_API FrameLayout
        : public Block,
          public virtual Layout
    {

    public:
        Anchor getHorizontalAnchor(const SharedWidget &widget) const;
        void setHorizontalAnchor(const SharedWidget &widget, Anchor value) const;

        Anchor getVerticalAnchor(const SharedWidget &widget) const;
        void setVerticalAnchor(const SharedWidget &widget, Anchor value) const;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        const SharedWidget &getWidget() const;

        ///////////////////////////////////////////////////////////

        bool dispatchEvent(Widget *target, const sf::Event &event) override;

        FrameLayout();
        virtual ~FrameLayout();

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

        SharedHolder m_holder;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP