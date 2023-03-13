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

    ////////////////////////////////////////////////////////////////

    bool FrameLayout::isValid() const
    {
        return (Block::isValid() && (!m_widget || m_widget->isValid()));
    }

    void FrameLayout::invalidate()
    {
        Block::invalidate();
        if (m_widget)
        {
            m_widget->invalidate();
        }
    }

    void FrameLayout::compact()
    {
        sf::Vector2f size(0, 0);
        if (m_widget)
        {
            m_widget->compact();
            size.x = m_widget->getWidth();
            size.y = m_widget->getHeight();
        }
        Block::compact();
        auto &margin = getMargin();
        setWidth(std::max(size.x, getMinWidth()) + margin.getHorizontal() + m_padding.getHorizontal());
        setHeight(std::max(size.y, getMinHeight()) + margin.getVertical() + m_padding.getVertical());
    }

    void FrameLayout::inflate(const sf::Vector2f &size, const Aligner *const aligner)
    {
        Block::inflate(size, aligner);
        if (m_widget)
        {
            m_widget->inflate({getWidth() - m_padding.getHorizontal(), getHeight() - m_padding.getVertical()}, nullptr);
        }
    }

    FrameLayout::FrameLayout()
        : m_widget(nullptr), m_padding(0) {}

    FrameLayout::~FrameLayout() {}

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        if (m_widget)
        {
            auto _states = states;
            auto &margin = getMargin();
            _states.transform.translate({m_padding.left, m_padding.top});
            target.draw(*m_widget, _states);
        }
    }

    void FrameLayout::onUpdate() const
    {
        Block::onUpdate();
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