#ifndef COLIB_SURFACE_HPP
#define COLIB_SURFACE_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Inflatable.hpp>

namespace co
{

    class COLIB_UI_API Surface
        : public Box,
          public virtual sf::Drawable,
          public virtual LeafNode,
          public virtual Inflatable
    {

    public:
        Node *getParent() const override final;

        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        Surface();
        virtual ~Surface();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        void onAttach(Node *parent) override final;
        void onDetach() override final;

    private:
        void update() const;

        mutable bool m_needUpdate;
        mutable sf::VertexArray m_array;

        sf::Color m_color;
        Node *m_parent;
    };

}

#endif // COLIB_SURFACE_HPP