#define COLIB_UI_EXPORTS
#include <CoLib/UI/Span.hpp>

namespace co
{

    Node *Span::getParent() const
    {
        return m_parent;
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