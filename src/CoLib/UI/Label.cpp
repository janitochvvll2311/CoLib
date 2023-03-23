#define COLIB_UI_EXPORTS
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Span.hpp>
#include <CoLib/UI/Label.hpp>

namespace co
{

    Node *Label::getParent() const
    {
        return m_root.getParent();
    }

    Label::Anchor Label::getHorizontalContentAnchor()
    {
        return m_root.getHorizontalAnchor(m_root.getChild(0));
    }

    void Label::setHorizontalContentAnchor(Anchor value)
    {
        m_root.setHorizontalAnchor(m_root.getChild(0), value);
    }

    Label::Anchor Label::getVerticalContentAnchor()
    {
        return m_root.getVerticalAnchor(m_root.getChild(0));
    }

    void Label::setVerticalContentAnchor(Anchor value)
    {
        m_root.setVerticalAnchor(m_root.getChild(0), value);
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
        return *(std::dynamic_pointer_cast<Span>(m_root.getChild(0)));
    }

    const Span &Label::getSpan() const
    {
        return *(std::dynamic_pointer_cast<Span>(m_root.getChild(0)));
    }

    sf::Vector2f Label::compact()
    {
        return m_root.compact();
    }

    sf::Vector2f Label::inflate(const sf::Vector2f &size)
    {
        return m_root.inflate(size);
    }

    void Label::place(const sf::Vector2f &position)
    {
        m_root.place(position);
    }

    bool Label::handleEvent(Node *target, const sf::Event &event)
    {
        return m_root.handleEvent(target, event);
    }

    bool Label::isValid() const
    {
        return m_root.isValid();
    }

    void Label::invalidate()
    {
        m_root.invalidate();
    }

    Label::Label()
        : m_root()
    {
        m_root.append(std::make_shared<Span>());
    }

    Label::~Label() {}

    //////////////////////////////////////////////////////////

    void Label::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(m_root, states);
    }

    void Label::onAttach(Node *parent)
    {
        m_root.attach(parent);
    }

    void Label::onDetach()
    {
        m_root.detach();
    }

    void Label::onUpdate() const
    {
        m_root.update(true);
    }

}