#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    const Thickness &FrameLayout::getPadding() const
    {
        return m_padding;
    }

    void FrameLayout::setPadding(const Thickness &value)
    {
        m_padding = value;
    }

    const SharedBackground &FrameLayout::getBackground() const
    {
        if (m_block)
        {
            return m_block->getBackground();
        }
        return NoBackground;
    }

    void FrameLayout::setBackground(const SharedBackground &value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setBackground(value);
    }

    f32t FrameLayout::getMinWidth() const
    {
        if (m_block)
        {
            return m_block->getMinWidth();
        }
        return 0;
    }

    void FrameLayout::setMinWidth(f32t value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setMinWidth(value);
    }

    f32t FrameLayout::getMaxWidth() const
    {
        if (m_block)
        {
            return m_block->getMaxWidth();
        }
        return std::numeric_limits<f32t>::infinity();
    }

    void FrameLayout::setMaxWidth(f32t value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setMaxWidth(value);
    }

    f32t FrameLayout::getMinHeight() const
    {
        if (m_block)
        {
            return m_block->getMinHeight();
        }
        return 0;
    }

    void FrameLayout::setMinHeight(f32t value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setMinHeight(value);
    }

    f32t FrameLayout::getMaxHeight() const
    {
        if (m_block)
        {
            return m_block->getMaxHeight();
        }
        return std::numeric_limits<f32t>::infinity();
    }

    void FrameLayout::setMaxHeight(f32t value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setMaxHeight(value);
    }

    const Thickness &FrameLayout::getMargin() const
    {
        if (m_block)
        {
            return m_block->getMargin();
        }
        return Thickness::Default;
    }

    void FrameLayout::setMargin(const Thickness &value)
    {
        if (!m_block)
        {
            m_block.reset(new Block());
        }
        m_block->setMargin(value);
    }

    ////////////////////////////////////////////////////////////////

    bool FrameLayout::isValid() const
    {
        return (Layout::isValid() && (!m_widget || m_widget->isValid()));
    }

    void FrameLayout::invalidate()
    {
        Layout::invalidate();
        if (m_widget)
        {
            m_widget->invalidate();
        }
    }

    void FrameLayout::compact()
    {
        sf::Vector2f size(m_padding.getHorizontal(), m_padding.getVertical());
        if (m_widget)
        {
            m_widget->compact();
            size.x += m_widget->getWidth();
            size.y += m_widget->getHeight();
        }
        if (m_block)
        {
            m_block->compact();
            auto &margin = m_block->getMargin();
            size.x = std::max(size.x, m_block->getMinWidth()) + margin.getHorizontal();
            size.y = std::max(size.y, m_block->getMinHeight()) + margin.getVertical();
            m_block->setWidth(size.x);
            m_block->setHeight(size.y);
        }
        setWidth(size.x);
        setHeight(size.y);
    }

    void FrameLayout::inflate(const sf::Vector2f &size, const Aligner *const aligner)
    {
        sf::Vector2f _size(std::max(getWidth(), size.x), std::max(getHeight(), size.y));
        if (m_block)
        {
            m_block->inflate(_size, nullptr);
            _size.x = m_block->getWidth();
            _size.y = m_block->getHeight();
        }
        Layout::inflate(_size, aligner);
        if (m_widget)
        {
            _size -= {m_padding.getHorizontal(), m_padding.getVertical()};
            m_widget->inflate(_size, nullptr);
        }
    }

    FrameLayout::FrameLayout()
        : m_widget(nullptr), m_padding(0) {}

    FrameLayout::~FrameLayout() {}

    const SharedBackground FrameLayout::NoBackground(nullptr);

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Layout::onDraw(target, states);
        auto _states = states;
        if (m_block)
        {
            target.draw(*m_block, states);
            auto &margin = m_block->getMargin();
            _states.transform.translate({margin.left, margin.top});
        }
        if (m_widget)
        {
            _states.transform.translate({m_padding.left, m_padding.top});
            target.draw(*m_widget, _states);
        }
    }

    void FrameLayout::onUpdate() const
    {
        Layout::onUpdate();
        if (m_block)
        {
            m_block->update(true);
        }
        if (m_widget)
        {
            m_widget->update(true);
        }
    }

    void FrameLayout::onAttach(const SharedWidget &widget)
    {
        m_widget = widget;
    }

    void FrameLayout::onDetach(const SharedWidget &widget)
    {
        m_widget = nullptr;
    }

}