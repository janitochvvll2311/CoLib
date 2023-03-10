#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    bool FrameLayout::isValid() const
    {
        return Layout::isValid() && (!m_widget || m_widget->isValid());
    }

    void FrameLayout::invalidate()
    {
        Layout::invalidate();
        if (m_widget)
        {
            m_widget->invalidate();
        }
    }

    void FrameLayout::compact(const sf::Vector2f &size)
    {
        
    }

    void FrameLayout::inflate(const Box &box)
    {
        
    }

    FrameLayout::FrameLayout()
        : m_widget() {}

    FrameLayout::~FrameLayout() {}

    ////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Widget::onDraw(target, states);
        if (m_widget)
        {
            auto _states = states;
            auto &padding = getPadding();
            _states.transform.translate({padding.left, padding.top});
            target.draw(*m_widget, _states);
        }
    }

    void FrameLayout::onAttach(const SharedWidget &widget)
    {
        Layout::onAttach(widget);
        m_widget = widget;
    }

    void FrameLayout::onDetach(const SharedWidget &widget)
    {
        Layout::onDetach(widget);
        m_widget.reset();
    }

}