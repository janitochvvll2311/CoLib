#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>

namespace co
{

    class COLIB_UI_API FrameLayout
        : public Block,
          public virtual Layout

    {

    public:
        szt getChildCount() const override final;
        SharedNode getChild(szt index) const override final;

        Anchor getHorizontalAnchor(const SharedNode &child) const;
        void setHorizontalAnchor(const SharedNode &child, Anchor value);

        Anchor getVerticalAnchor(const SharedNode &child) const;
        void setVerticalAnchor(const SharedNode &child, Anchor value);

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAppend(const SharedNode &child) override final;
        void onRemove(const SharedNode &child) override final;

        bool dispatchChildrenEvents(Node *target, const sf::Event &event) const override;

        sf::Vector2f compactContent() const override final;
        void inflateContent() const override final;

    private:
        struct Holder;
        using SharedHolder = std::shared_ptr<Holder>;

        struct Holder
        {
            Holder() = default;
            virtual ~Holder() = default;

            SharedNode child;
            Anchor hAnchor;
            Anchor vAnchor;
        };

        SharedHolder m_holder;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP