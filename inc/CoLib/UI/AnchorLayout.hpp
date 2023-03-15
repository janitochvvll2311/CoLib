#ifndef COLIB_ANCHOR_LAYOUT_HPP
#define COLIB_ANCHOR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/GroupLayout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API AnchorLayout
        : public GroupLayout
    {

    public:
        Anchor getHorizontalAnchor(const SharedWidget &widget) const;
        void setHorizontalAnchor(const SharedWidget &widget, Anchor value);

        Anchor getVerticalAnchor(const SharedWidget &widget) const;
        void setVerticalAnchor(const SharedWidget &widget, Anchor value);

        //////////////////////////////////////////////////////////////////////////

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        AnchorLayout();
        virtual ~AnchorLayout();

    protected:
        sf::Vector2f getContentSize() const override;

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

        //////////////////////////////////////////////////////

        SharedHolder getHolder(const SharedWidget &widget) const;

        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_ANCHOR_LAYOUT_HPP