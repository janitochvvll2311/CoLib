#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/Thickness.hpp>

namespace co
{

    class Background;
    using SharedBackground = std::shared_ptr<Background>;

    class Block;
    using SharedBlock = std::shared_ptr<Block>;

    ///////////////////////////////////////////////////////

    class COLIB_UI_API FrameLayout : public Layout
    {

    public:
        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        const SharedBackground &getBackground() const;
        void setBackground(const SharedBackground &value);

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        ///////////////////////////////////////////////////

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size, const Aligner *const aligner = nullptr) override;

        FrameLayout();
        virtual ~FrameLayout();

        static const SharedBackground NoBackground;

    protected:
        void
        onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        SharedBlock m_block;
        Thickness m_padding;
        SharedWidget m_widget;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP