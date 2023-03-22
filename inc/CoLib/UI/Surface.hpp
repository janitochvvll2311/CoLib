#ifndef COLIB_SURFACE_HPP
#define COLIB_SURFACE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Inflatable.hpp>
#include <CoLib/UI/Updatable.hpp>

namespace sf
{
    class Texture;
}

namespace co
{

    using SharedTexture = std::shared_ptr<sf::Texture>;

    ////////////////////////////////////////////////////////

    class COLIB_UI_API Surface
        : public Box,
          public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable,
          public virtual Updatable
    {

    public:
        Node *getParent() const override final;

        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        const SharedTexture &getTexture() const;
        void setTexture(const SharedTexture &value);

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        bool isValid() const override final;
        void invalidate() override final;

        Surface();
        virtual ~Surface();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

        void onUpdate() const override;

    private:
        mutable bool m_isValid;
        mutable sf::VertexArray m_array;

        sf::Color m_color;
        SharedTexture m_texture;
        Node *m_parent;
    };

}

#endif // COLIB_SURFACE_HPP