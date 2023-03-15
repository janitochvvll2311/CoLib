#ifndef COLIB_GROUP_LAYOUT_HPP
#define COLIB_GROUP_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>

namespace co
{

    class WidgetHolder;
    using SharedHolder = std::shared_ptr<WidgetHolder>;

    ///////////////////////////////////////////////

    class COLIB_UI_API GroupLayout
        : public Block
    {

    public:
        szt getChildCount() const override;
        SharedNode getChild(szt index) const override;

        bool dispatchEvent(Node *target, const sf::Event &event) override;
        bool bubbleEvent(Node *target, const sf::Event &event) override;

        GroupLayout();
        virtual ~GroupLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAppend(const SharedNode &widget) override;
        void onRemove(const SharedNode &widget) override;

        SharedHolder getHolder(const SharedWidget &widget) const;
        const std::list<SharedHolder> &getHolders() const;
        virtual SharedHolder createHolder() const;

    private:
        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_GROUP_LAYOUT_HPP