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

    void FrameLayout::compact()
    {
        Layout::compact();
        if (m_widget)
        {
            m_widget->compact();
            setWidth(std::max(getWidth(), m_widget->getWidth() + getHorizontalSpacing()));
            setHeight(std::max(getHeight(), m_widget->getHeight() + getVerticalSpacing()));
        }
    }

    void FrameLayout::inflate(const Box &box)
    {
        Layout::inflate(box);
        if (m_widget)
        {
            auto &padding = getPadding();
            m_widget->inflate({getWidth() - padding.getHorizontal(), getHeight() - padding.getVertical()});
        }
    }

    FrameLayout::FrameLayout()
        : m_widget() {}

    FrameLayout::~FrameLayout() {}

    ////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Layout::onDraw(target, states);
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