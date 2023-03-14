#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Label.hpp>

namespace co
{

    Label::Alignment Label::getHorizontalContentAlignment() const
    {
        return m_root.getHorizontalAlignment(m_root.getWidget());
    }

    void Label::setHorizontalContentAlignment(Alignment value)
    {
        m_root.setHorizontalAlignment(m_root.getWidget(), value);
    }

    Label::Alignment Label::getVerticalContentAlignment() const
    {
        return m_root.getVerticalAlignment(m_root.getWidget());
    }

    void Label::setVerticalContentAlignment(Alignment value)
    {
        m_root.setVerticalAlignment(m_root.getWidget(), value);
    }

    Block &Label::getBlock()
    {
        return m_root;
    }

    const Block &Label::getBlock() const
    {
        return m_root;
    }

    Span &Label::getSpan()
    {
        return *(Span *)(m_root.getWidget().get());
    }

    const Span &Label::getSpan() const
    {
        return *(Span *)(m_root.getWidget().get());
    }

    /////////////////////////////////////////////

    bool Label::isValid() const
    {
        return m_root.isValid();
    }

    void Label::invalidate()
    {
        m_root.invalidate();
    }

    void Label::compact()
    {
        m_root.compact();
    }

    void Label::inflate(const sf::Vector2f &size)
    {
        m_root.inflate(size);
    }

    Label::Label()
        : m_root()
    {
        m_root.attach(std::make_shared<Span>());
    }

    Label::~Label() {}

    ///////////////////////////////////////////////////////////////////////////////////////////////

    void Label::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(m_root, states);
    }

    void Label::onUpdate() const
    {
        m_root.update(true);
    }

}