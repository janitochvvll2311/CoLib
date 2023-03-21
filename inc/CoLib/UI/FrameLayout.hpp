#ifndef COLIB_FRAME_LAYOUT_HPP
#define COLIB_FRAME_LAYOUT_HPP

#include <CoLib/UI/Block.hpp>

namespace co
{

    class COLIB_UI_API FrameLayout
        : public Block

    {

    public:
        szt getChildCount() const override final;
        SharedNode getChild(szt index) const override final;

        FrameLayout();
        virtual ~FrameLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAppend(const SharedNode &child) override final;
        void onRemove(const SharedNode &child) override final;

        sf::Vector2f compactContent() const override final;
        void inflateContent() const override final;

    private:
        struct Holder;
        using SharedHolder = std::shared_ptr<Holder>;

        struct Holder
        {
            SharedNode child;
            Anchor hAnchor;
            Anchor vAnchor;
        };

        SharedHolder m_holder;
    };

}

#endif // COLIB_FRAME_LAYOUT_HPP