#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/Thickness.hpp>

namespace co
{

    class COLIB_UI_API FrameLayout : public Layout
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
        SharedWidget m_widget;
        Thickness m_padding;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP