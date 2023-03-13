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
        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size, const Aligner *const aligner = nullptr) override;

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        Thickness m_padding;
        SharedWidget m_widget;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP