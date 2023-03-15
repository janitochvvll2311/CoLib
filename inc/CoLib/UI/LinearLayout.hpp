#ifndef COLIB_LINEAR_LAYOUT_HPP
#define COLIB_LINEAR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API LinearLayout
        : public Block,
          public virtual Layout
    {

    public:
        enum Orientation
        {
            Horizontal,
            Vertical
        };

        using Anchor = Anchor;

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

        ///////////////////////////////////////////////////////////

        bool dispatchEvent(Widget *target, const sf::Event &event) override;
        bool bubbleEvent(Widget *target, const sf::Event &event) override;
        
        LinearLayout();
        virtual ~LinearLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        class WidgetHolder;
        using SharedHolder = std::shared_ptr<WidgetHolder>;

        ////////////////////////////////////////////////////////////

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

        //////////////////////////////////////////////////////////////

        SharedHolder getHolder(const SharedWidget &widget) const;

        Orientation m_orientation;
        bool m_isReverse;
        Anchor m_cAnchor;
        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP