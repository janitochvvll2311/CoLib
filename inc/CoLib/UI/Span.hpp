#ifndef COLIB_SPAN_HPP
#define COLIB_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <CoLib/UI/Node.hpp>
#include <CoLib/UI/Inflatable.hpp>

namespace co
{

    class COLIB_UI_API Span
        : public sf::Text,
          public virtual LeafNode,
          public virtual Inflatable
    {
    public:
        Node *getParent() const override final;

        sf::Vector2f compact() override final;
        sf::Vector2f inflate(const sf::Vector2f &size) override final;
        void place(const sf::Vector2f &position) override final;

        Span();
        virtual ~Span();

    protected:
        void onAttach(Node *parent) override final;
        void onDetach() override final;

    private:
        Node *m_parent;
    };

}

#endif // COLIB_SPAN_HPP