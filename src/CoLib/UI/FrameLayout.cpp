#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    bool FrameLayout::isValid() const
    {
        return Layout::isValid() && (!m_holder || m_holder->getWidget()->isValid());
    }

    void FrameLayout::invalidate()
    {
        Layout::invalidate();
        if (m_holder)
        {
            m_holder->getWidget()->invalidate();
        }
    }

    void FrameLayout::compact()
    {
        Layout::compact();
        if (m_holder)
        {
            auto &widget = m_holder->getWidget();
            widget->compact();
            setWidth(std::max(getWidth(), widget->getWidth() + getHorizontalSpacing()));
            setHeight(std::max(getHeight(), widget->getHeight() + getVerticalSpacing()));
        }
    }

    void FrameLayout::inflate(const Box &box)
    {
        Layout::inflate(box);
        if (m_holder)
        {
            auto &padding = getPadding();
            m_holder->getWidget()->inflate({getWidth() - padding.getHorizontal(), getHeight() - padding.getVertical()});
        }
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr) {}

    FrameLayout::~FrameLayout() {}

    ////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Layout::onDraw(target, states);
        if (m_holder)
        {
            auto _states = states;
            auto &padding = getPadding();
            _states.transform.translate({padding.left, padding.top});
            target.draw(*(m_holder->getWidget()), _states);
        }
    }

    void FrameLayout::onAttach(const SharedWidget &widget)
    {
        Layout::onAttach(widget);
        m_holder.reset(new WidgetHolder(widget));
    }

    void FrameLayout::onDetach(const SharedWidget &widget)
    {
        Layout::onDetach(widget);
        m_holder.reset();
    }

    //////////////////////////////////////////////////////////////

    const SharedWidget &FrameLayout::WidgetHolder::getWidget() const
    {
        return m_widget;
    }

    FrameLayout::WidgetHolder::WidgetHolder(const SharedWidget &widget)
        : m_widget(widget) {}

    FrameLayout::WidgetHolder::~WidgetHolder() {}

}