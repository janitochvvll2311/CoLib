#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Label.hpp>

namespace co
{

    Label::Anchor Label::getHorizontalContentAnchor() const
    {
        return getHorizontalAnchor(m_span);
    }

    void Label::setHorizontalContentAnchor(Anchor value)
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
        append(m_span);
    }

    Label::~Label() {}

    //////////////////////////////////////////////////////////////////

    void Label::onAppend(const SharedNode &node)
    {
        if (node != m_span)
        {
            throw InvalidOperationException("Label not support child changes");
        }
        FrameLayout::onAppend(node);
    }

    void Label::onRemove(const SharedNode &node)
    {
        throw InvalidOperationException("Label not support child changes");
    }

}