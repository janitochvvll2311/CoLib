#ifndef COLIB_BLOCK_HPP
#define COLIB_BLOCK_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Inflatable.hpp>
#include <CoLib/UI/Updatable.hpp>

namespace co
{

    using SharedDrawable = std::shared_ptr<sf::Drawable>;

    ////////////////////////////////////////////////////

    class COLIB_UI_API Block
        : public Box,
          public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable,
          public virtual Updatable
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

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        bool handleEvent(Node* target, const sf::Event& event) override;

        bool isValid() const override final;
        void invalidate() override final;

        sf::Vector2f getInnerSize() const;

        Block();
        virtual ~Block();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

        void onUpdate() const override final;

        virtual sf::Vector2f compactContent() const;
        virtual void inflateContent() const;
        virtual void placeContent(const sf::Vector2f& origin) const;

        virtual void updateContent() const;
        virtual void drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const;

    private:
        mutable bool m_isValid;
        mutable SharedDrawable m_background;

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