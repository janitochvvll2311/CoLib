#ifndef COLIB_LINEAR_LAYOUT_HPP
#define COLIB_LINEAR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/GroupLayout.hpp>

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

        Anchor getAnchor(const SharedNode &child) const;
        void setAnchor(const SharedNode &child, Anchor value);

        f32t getWeight(const SharedNode &child) const;
        void setWeight(const SharedNode &child, f32t value);

        Orientation getOrientation() const;
        void setOrientation(Orientation value);

        bool isReverse() const;
        void setReverse(bool value = true);

        Anchor getContentAnchor() const;
        void setContentAnchor(Anchor value);

        //////////////////////////////////////////////////////////////

        LinearLayout();
        virtual ~LinearLayout();

    protected:
        sf::Vector2f compactContent() const override final;
        void inflateContent() const override final;
        void placeContent(const sf::Vector2f &origin) const override final;

        SharedHolder createHolder() const override;

    private:
        struct LinearHolder : public Holder
        {
            LinearHolder() = default;
            virtual ~LinearHolder() = default;

            Anchor anchor;
            f32t weight;
            sf::Vector2f size;
        };
        mutable f32t m_length;

        Orientation m_orientation;
        bool m_isReverse;
        Anchor m_cAnchor;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP