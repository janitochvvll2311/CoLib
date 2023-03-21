#ifndef COLIB_SPAN_HPP
#define COLIB_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <CoLib/UI/Node.hpp>

namespace co
{

    class COLIB_UI_API Span
        : public sf::Text,
          public virtual LeafNode
    {
    public:
        Node *getParent() const override final;

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