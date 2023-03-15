#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Label.hpp>

namespace co
{

    Label::Anchor Label::getHorizontalContentAnchor() const
    {
        return getHorizontalAnchor(m_span);
    }

    void Label::setHorizontalContentAlignment(Anchor value)
    {
        setHorizontalAnchor(m_span, value);
    }

    Label::Anchor Label::getVerticalContentAlignment() const
    {
        return getVerticalAnchor(m_span);
    }

    void Label::setVerticalContentAnchor(Anchor value)
    {
        setVerticalAnchor(m_span, value);
    }

    const SharedSpan &Label::getSpan() const
    {
        return m_span;
    }

    Label::Label()
        : m_span(new Span())
    {
        attach(m_span);
    }

    Label::~Label() {}

    //////////////////////////////////////////////////////////////////

    void Label::onAttach(const SharedWidget &widget)
    {
        if (widget != m_span)
        {
            throw InvalidOperationException();
        }
        FrameLayout::onAttach(widget);
    }

    void Label::onDetach(const SharedWidget &widget)
    {
        throw InvalidOperationException();
    }

}