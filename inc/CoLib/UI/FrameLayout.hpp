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
        using Alignment = Anchor;

        Alignment getHorizontalAlignment(const SharedWidget &widget) const;
        void setHorizontalAlignment(const SharedWidget &widget, Alignment value) const;

        Alignment getVerticalAlignment(const SharedWidget &widget) const;
        void setVerticalAlignment(const SharedWidget &widget, Alignment value) const;

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        const SharedWidget &getWidget() const;

        ///////////////////////////////////////////////////////////

        bool handleEvent(const sf::Event &event) override;

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
            Alignment getHorizontalAlignment() const;
            void setHorizontalAlignment(Alignment value);

            Alignment getVerticalAlignment() const;
            void setVerticalAlignment(Alignment value);

            WidgetHolder();
            virtual ~WidgetHolder();

        private:
            Alignment m_hAlignment;
            Alignment m_vAlignment;
        };

        SharedHolder m_holder;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP