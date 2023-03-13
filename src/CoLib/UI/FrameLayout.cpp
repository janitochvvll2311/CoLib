#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
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
        if (m_widget)
        {
            m_widget->compact();
            setWidth(m_widget->getWidth() + m_padding.getHorizontal());
            setHeight(m_widget->getHeight() + m_padding.getVertical());
        }
        else
        {
            setWidth(m_padding.getHorizontal());
            setHeight(m_padding.getVertical());
        }
    }

    void FrameLayout::inflate(const sf::Vector2f &size, const Aligner *const aligner)
    {
        sf::Vector2f _size(std::max(getWidth(), size.x), std::max(getHeight(), size.y));
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

    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Layout::onDraw(target, states);
        if (m_widget)
        {
            auto _states = states;
            _states.transform.translate({m_padding.left, m_padding.top});
            target.draw(*m_widget, _states);
        }
    }

    void FrameLayout::onUpdate() const
    {
        Layout::onUpdate();
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