#ifndef COLIB_BLOCK_HPP
#define COLIB_BLOCK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Inflatable.hpp>

namespace co
{

    using SharedDrawable = std::shared_ptr<sf::Drawable>;

    ////////////////////////////////////////////////////

    class COLIB_UI_API Block
        : public Box,
          public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable
    {
    public:
        Node *getParent() const override final;

        const SharedDrawable &getBackground() const;
        void setBackground(const SharedDrawable &value);

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        void compact() override final;
        void inflate(const sf::Vector2f &size) override final;

        Block();
        virtual ~Block();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

    private:
        void update() const;

        SharedDrawable m_background;
        Thickness m_margin;
        Thickness m_padding;
        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;
        Node *m_parent;
    };

}

#endif // COLIB_BLOCK_HPP