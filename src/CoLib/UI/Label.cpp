#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Label.hpp>

namespace co
{

    Label::Alignment Label::getHorizontalContentAlignment() const
    {
        return getHorizontalAlignment(m_span);
    }

    void Label::setHorizontalContentAlignment(Alignment value)
    {
        setHorizontalAlignment(std::static_pointer_cast<Widget>(m_span), value);
    }

    Label::Alignment Label::getVerticalContentAlignment() const
    {
        return getVerticalAlignment(m_span);
    }

    void Label::setVerticalContentAlignment(Alignment value)
    {
        setVerticalAlignment(m_span, value);
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
        if (getWidget())
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