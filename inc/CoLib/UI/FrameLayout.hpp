#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/Thickness.hpp>

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
        enum Alignment
        {
            Start,
            Center,
            End
        };

        Alignment getHorizontalAlignment(const SharedWidget &widget) const;
        void setHorizontalAlignment(const SharedWidget &widget, Alignment value) const;

        Alignment getVerticalAlignment(const SharedWidget &widget) const;
        void setVerticalAlignment(const SharedWidget &widget, Alignment value) const;

        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        f32t getInnerWidth() const override;
        f32t getInnerHeight() const override;

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        class WidgetHolder
        {
        public:
            Alignment getHorizontalAlignment() const;
            void setHorizontalAlignment(Alignment value);

            Alignment getVerticalAlignment() const;
            void setVerticalAlignment(Alignment value);

            const SharedWidget &getWidget() const;
            void setWidget(const SharedWidget &value);

            WidgetHolder();
            ~WidgetHolder();

        private:
            Alignment m_hAlignment;
            Alignment m_vAlignment;
            SharedWidget m_widget;
        };

        Thickness m_padding;
        std::shared_ptr<WidgetHolder> m_holder;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP