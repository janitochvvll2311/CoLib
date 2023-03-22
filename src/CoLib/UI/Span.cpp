#define COLIB_UI_EXPORTS
#include <CoLib/UI/Span.hpp>

namespace co
{

    Node *Span::getParent() const
    {
        return m_parent;
    }

    sf::Vector2f Span::compact()
    {
        auto bounds = getLocalBounds();
        return {bounds.width, bounds.height};
    }

    sf::Vector2f Span::inflate(const sf::Vector2f &size)
    {
        return compact();
    }

    void Span::place(const sf::Vector2f &position)
    {
        auto bounds = getLocalBounds();
        setPosition({position.x - bounds.left, position.y - bounds.top});
    }

    Span::Span()
        : m_parent(nullptr) {}

    Span::~Span() {}

    //////////////////////////////////////////

    void Span::onAttach(Node *parent)
    {
        m_parent = parent;
    }

    void Span::onDetach()
    {
        m_parent = nullptr;
    }

}