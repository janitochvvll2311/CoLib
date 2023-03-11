#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Layout.hpp>

namespace co
{

    const Thickness &Layout::getPadding() const
    {
        return m_padding;
    }

    void Layout::setPadding(const Thickness &value)
    {
        m_padding = value;
    }

    f32t Layout::getInnerWidth() const
    {
        return getWidth() - m_padding.getHorizontal();
    }

    f32t Layout::getInnerHeight() const
    {
        return getHeight() - m_padding.getVertical();
    }

    f32t Layout::getHorizontalSpacing() const
    {
        return Widget::getHorizontalSpacing() + m_padding.getHorizontal();
    }

    f32t Layout::getVerticalSpacing() const
    {
        return Widget::getVerticalSpacing() + m_padding.getVertical();
    }

    //////////////////////////////////////////////////////////

    void Layout::attach(const SharedWidget &widget)
    {
        if (widget->m_parent || widget.get() == this)
        {
            throw InvalidOperationException();
        }
        auto parent = m_parent;
        while (parent)
        {
            if (parent == this)
            {
                throw InvalidOperationException();
            }
            parent = parent->m_parent;
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

    Layout::Layout()
        : Widget(), m_padding() {}

    Layout::~Layout() {}

    /////////////////////////////////////////////////////////////////////

    void Layout::onAttach(const SharedWidget &widget) {}

    void Layout::onDetach(const SharedWidget &widget) {}

}