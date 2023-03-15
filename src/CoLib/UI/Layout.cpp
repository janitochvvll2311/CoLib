#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Layout.hpp>

namespace co
{

    void Layout::attach(const SharedWidget &widget)
    {
        if (widget->m_parent != nullptr)
        {
            throw InvalidOperationException();
        }
        widget->m_parent = this;
        onAttach(widget);
    }

    void Layout::detach(const SharedWidget &widget)
    {
        if (widget->m_parent != this)
        {
            throw InvalidOperationException();
        }
        widget->m_parent = nullptr;
        onDetach(widget);
    }

    Layout::Layout() {}
    Layout::Layout::~Layout() {}

    const SharedWidget Layout::NoWidget(nullptr);

    ////////////////////////////////////////////////////

    void Layout::onAttach(const SharedWidget &widget) {}
    void Layout::onDetach(const SharedWidget &widget) {}

}