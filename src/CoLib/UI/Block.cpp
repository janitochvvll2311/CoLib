#define COLIB_UI_EXPORTS
#include <limits>
#include <math.h>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Block.hpp>

namespace co
{

    Node *Block::getParent() const
    {
        return m_parent;
    }

    const SharedDrawable &Block::getBackground() const
    {
        return m_background;
    }

    void Block::setBackground(const SharedDrawable &value)
    {
        m_background = value;
    }

    const Thickness &Block::getMargin() const
    {
        return m_margin;
    }

    void Block::setMargin(const Thickness &value)
    {
        m_margin = value;
    }

    const Thickness &Block::getPadding() const
    {
        return m_padding;
    }

    void Block::setPadding(const Thickness &value)
    {
        m_padding = value;
    }

    f32t Block::getMinWidth() const
    {
        return m_minWidth;
    }

    void Block::setMinWidth(f32t value)
    {
        m_minWidth = value;
    }

    f32t Block::getMaxWidth() const
    {
        return m_maxWidth;
    }

    void Block::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
    }

    f32t Block::getMinHeight() const
    {
        return m_minHeight;
    }

    void Block::setMinHeight(f32t value)
    {
        m_minHeight = value;
    }

    f32t Block::getMaxHeight() const
    {
        return m_maxHeight;
    }

    void Block::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
    }

    sf::Vector2f Block::compact()
    {
        auto cSize = compactContent();
        setWidth(std::max(m_minWidth, cSize.x) + m_margin.getHorizontal() + m_padding.getHorizontal());
        setHeight(std::max(m_minHeight, cSize.y) + m_margin.getVertical() + m_padding.getVertical());
        return {getWidth(), getHeight()};
    }

    sf::Vector2f Block::inflate(const sf::Vector2f &size)
    {
        sf::Vector2f outerSize(std::max(getWidth(), std::min(size.x, m_maxWidth)),
                               std::max(getHeight(), std::min(size.y, m_maxHeight)));
        setWidth(outerSize.x - m_margin.getHorizontal());
        setHeight(outerSize.y - m_margin.getVertical());
        inflateContent();
        return outerSize;
    }

    void Block::place(const sf::Vector2f &position)
    {
        setLeft(position.x + m_margin.left);
        setTop(position.y + m_margin.top);
        placeContent({getLeft() + m_padding.left, getTop() + m_padding.top});
    }

    bool Block::handleEvent(Node *target, const sf::Event &event)
    {
        if (!target && m_background)
        {
            auto node = std::dynamic_pointer_cast<Node>(m_background);
            if (node)
            {
                node->dispatchEvent(nullptr, event);
            }
        }
        return false;
    }

    bool Block::isValid() const
    {
        return m_isValid;
    }

    void Block::invalidate()
    {
        m_isValid = false;
        auto parent = getParent();
        while (parent)
        {
            auto updatable = dynamic_cast<Updatable *>(parent);
            if (updatable)
            {
                updatable->invalidate();
                break;
            }
            parent = parent->getParent();
        }
    }

    sf::Vector2f Block::getInnerSize() const
    {
        return {getWidth() - m_padding.getHorizontal(), getHeight() - m_padding.getVertical()};
    }

    Block::Block()
        : m_isValid(false), m_background(nullptr),
          m_margin(0), m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_parent(nullptr) {}

    Block::~Block() {}

    /////////////////////////////////////////////////////////////////////////////////////////////

    void Block::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update(false);
        if (m_background)
        {
            target.draw(*m_background, states);
        }
        drawContent(target, states);
    }

    void Block::onAttach(Node *parent)
    {
        m_parent = parent;
    }

    void Block::onDetach()
    {
        m_parent = nullptr;
    }

    void Block::onUpdate() const
    {
        if (m_background)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_background);
            if (inflatable)
            {
                inflatable->compact();
                inflatable->inflate({getWidth(), getHeight()});
                inflatable->place({getLeft(), getTop()});
            }
            auto updatable = std::dynamic_pointer_cast<Updatable>(m_background);
            if (updatable)
            {
                updatable->update(true);
            }
        }
        updateContent();
        m_isValid = true;
    }

    sf::Vector2f Block::compactContent() const
    {
        return {0, 0};
    }

    void Block::inflateContent() const {}
    void Block::placeContent(const sf::Vector2f &origin) const {}
    void Block::updateContent() const {}
    void Block::drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const {}

}