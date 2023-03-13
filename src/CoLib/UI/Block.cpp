#include <limits>
#include <SFML/Graphics/RenderTarget.hpp>
#include <CoLib/UI/Block.hpp>

namespace co
{

    const SharedBackground &Block::getBackground() const
    {
        return m_background;
    }

    void Block::setBackground(const SharedBackground &value)
    {
        m_background = value;
    }

    //////////////////////////////////////////////////////////

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

    const Thickness &Block::getMargin() const
    {
        return m_margin;
    }

    void Block::setMargin(const Thickness &value)
    {
        m_margin = value;
    }

    f32t Block::getOuterWidth() const
    {
        return getWidth() + m_margin.getHorizontal();
    }

    f32t Block::getOuterHeight() const
    {
        return getHeight() + m_margin.getVertical();
    }

    /////////////////////////////////////////////////////////

    void Block::compact()
    {
        Widget::compact();
        setWidth(m_minWidth + m_margin.getHorizontal());
        setHeight(m_minHeight + m_margin.getVertical());
    }

    void Block::inflate(const sf::Vector2f &size)
    {
        sf::Vector2f _size(std::max(getWidth(), std::min(size.x, m_maxWidth + m_margin.getHorizontal())),
                           std::max(getHeight(), std::min(size.y, m_maxHeight + m_margin.getVertical())));
        Widget::inflate(_size);
        shrink(m_margin);
        if (m_background)
        {
            m_background->inflate({getWidth(), getHeight()});
        }
    }

    Block::Block()
        : m_background(),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_margin(0) {}

    Block::~Block() {}

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Block::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background)
        {
            target.draw(*m_background, states);
        }
        Widget::onDraw(target, states);
    }

    void Block::onUpdate() const
    {
        Widget::onUpdate();
        if (m_background)
        {
            m_background->update(true);
        }
    }

}