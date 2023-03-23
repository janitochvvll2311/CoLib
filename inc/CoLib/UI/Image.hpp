#ifndef COLIB_IMAGE_HPP
#define COLIB_IMAGE_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class Surface;
    class Block;

    /////////////////////////////////////////////////

    class COLIB_UI_API Image
        : public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable,
          public virtual Updatable
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

        Surface &getSurface();
        const Surface &getSurface() const;

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        bool handleEvent(Node *target, const sf::Event &event) override;

        bool isValid() const override final;
        void invalidate() override final;

        Image();
        virtual ~Image();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

        void onUpdate() const override final;

    private:
        FrameLayout m_root;
    };

}

#endif // COLIB_IMAGE_HPP