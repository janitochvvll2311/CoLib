#ifndef COLIB_LINEAR_LAYOUT_HPP
#define COLIB_LINEAR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/GroupLayout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API LinearLayout
        : public GroupLayout
    {

    public:
        enum Orientation
        {
            Horizontal,
            Vertical
        };

        Anchor getAnchor(const SharedWidget &widget) const;
        void setAnchor(const SharedWidget &widget, Anchor value);

        Orientation getOrientation() const;
        void setOritentation(Orientation value);

        bool isReverse() const;
        void setReverse(bool value = true);

        Anchor getContentAnchor() const;
        void setContentAnchor(Anchor value);

        //////////////////////////////////////////////////////////////

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        LinearLayout();
        virtual ~LinearLayout();

    protected:
        sf::Vector2f getContentSize() const override;
        SharedHolder createHolder() const override;

    private:
        class WidgetHolder : public co::WidgetHolder
        {
        public:
            Anchor getAnchor() const;
            void setAnchor(Anchor value);

            WidgetHolder();
            virtual ~WidgetHolder();

        private:
            Anchor m_anchor;
        };

        Orientation m_orientation;
        bool m_isReverse;
        Anchor m_cAnchor;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP