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

    void Block::compact()
    {
        setLeft(0);
        setTop(0);
        setWidth(m_minWidth + m_margin.getHorizontal() + m_padding.getHorizontal());
        setHeight(m_minHeight + m_margin.getVertical() + m_padding.getVertical());
    }

    void Block::inflate(const sf::Vector2f &size)
    {
        setLeft(0);
        setTop(0);
        setWidth(std::max(getWidth(), std::min(size.x, m_maxWidth)));
        setHeight(std::max(getHeight(), std::min(size.y, m_maxHeight)));
        shrink(m_margin);
        update();
    }

    Block::Block()
        : m_background(nullptr),
          m_margin(0), m_padding(0),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_parent(nullptr) {}

    Block::~Block() {}

    /////////////////////////////////////////////////////////////////////////////////////////////

    void Block::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background)
        {
            auto _states = states;
            _states.transform.translate({getLeft(), getTop()});
            target.draw(*m_background, _states);
        }
    }

    void Block::onAttach(Node *parent)
    {
        m_parent = parent;
    }

    void Block::onDetach()
    {
        m_parent = nullptr;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    void Block::update() const
    {
        if (m_background)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_background);
            if (inflatable)
            {
                inflatable->compact();
                inflatable->inflate({getWidth(), getHeight()});
            }
        }
    }

}