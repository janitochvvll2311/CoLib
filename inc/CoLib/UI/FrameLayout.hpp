#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Layout.hpp>

namespace co
{

    class COLIB_UI_API FrameLayout : public Layout
    {

    public:
        bool isValid() const override;
        void invalidate() override;

        void compact(const sf::Vector2f& size) override;
        void inflate(const Box &box) override;

        FrameLayout();
        ~FrameLayout();

    protected:
        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        SharedWidget m_widget;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP