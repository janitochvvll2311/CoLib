#ifndef COLIB_LABEL_HPP
#define COLIB_LABEL_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class Span;
    class Block;

    //////////////////////////////////////////////

    class COLIB_UI_API Label
        : public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable
    {

    public:
        using Anchor = FrameLayout::Anchor;

        Node *getParent() const override final;

        Anchor getHorizontalContentAnchor();
        void setHorizontalContentAnchor(Anchor value);

        Anchor getVerticalContentAnchor();
        void setVerticalContentAnchor(Anchor value);

        Block &getBlock();
        const Block &getBlock() const;

        Span &getSpan();
        const Span &getSpan() const;

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        Label();
        virtual ~Label();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

    private:
        FrameLayout m_root;
    };

}

#endif // COLIB_LABEL_HPP