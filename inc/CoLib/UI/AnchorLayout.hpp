#ifndef COLIB_ANCHOR_LAYOUT_HPP
#define COLIB_ANCHOR_LAYOUT_HPP

#include <CoLib/UI/GroupLayout.hpp>

namespace co
{

    class COLIB_UI_API AnchorLayout
        : public GroupLayout
    {

    public:
        Anchor getHorizontalAnchor(const SharedNode &child) const;
        void setHorizontalAnchor(const SharedNode &child, Anchor value);

        Anchor getVerticalAnchor(const SharedNode &child) const;
        void setVerticalAnchor(const SharedNode &child, Anchor value);

        AnchorLayout();
        virtual ~AnchorLayout();

    protected:
        virtual sf::Vector2f compactContent() const override final;
        virtual void inflateContent() const override final;

        SharedHolder createHolder() const override final;

    private:
        struct AnchorHolder
            : public Holder
        {
            Anchor hAnchor;
            Anchor vAnchor;
        };
    };

}

#endif // COLIB_ANCHOR_LAYOUT_HPP