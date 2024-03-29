#ifndef COLIB_GROUP_LAYOUT_HPP
#define COLIB_GROUP_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>

namespace co
{

    class COLIB_UI_API GroupLayout
        : public Block
    {

    public:
        szt getChildCount() const override final;
        SharedNode getChild(szt index) const override final;

        GroupLayout();
        virtual ~GroupLayout();

    protected:
        struct Holder;
        using SharedHolder = std::shared_ptr<Holder>;

        void onAppend(const SharedNode &child) override final;
        void onRemove(const SharedNode &child) override final;

        bool dispatchChildrenEvents(Node *target, const sf::Event &event) const override;

        void updateContent() const override final;
        void drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual SharedHolder createHolder() const;
        const std::list<SharedHolder> &getHolders() const;

        SharedHolder getHolder(szt index) const;
        SharedHolder getHolder(const SharedNode &child) const;

        struct Holder
        {
            Holder() = default;
            virtual ~Holder() = default;

            SharedNode child;
        };

    private:
        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_GROUP_LAYOUT_HPP