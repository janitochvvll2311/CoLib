#ifndef COLIB_LINEAR_LAYOUT_HPP
#define COLIB_LINEAR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Layout.hpp>

namespace co
{

    class COLIB_UI_API LinearLayout : public Layout
    {

    public:
        enum Orientation
        {
            Horizontal,
            Vertical
        };

        ////////////////////////////////////////////////////////

        Orientation getOrientation() const;
        void setOrientation(Orientation value);

        ////////////////////////////////////////////////////////

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const Box &box) override;

        LinearLayout();
        ~LinearLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        std::list<SharedWidget> m_widgets;

        Orientation m_orientation;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP