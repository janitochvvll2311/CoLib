#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/LinearLayout.hpp>

namespace co
{

    LinearLayout::Orientation LinearLayout::getOrientation() const
    {
        return m_orientation;
    }

    void LinearLayout::setOrientation(Orientation value)
    {
        m_orientation = value;
    }

    ///////////////////////////////////////////////////////////////

    bool LinearLayout::isValid() const
    {
        if (!Layout::isValid())
        {
            return false;
        }
        for (auto &widget : m_widgets)
        {
            if (!widget->isValid())
            {
                return false;
            }
        }
        return true;
    }

    void LinearLayout::invalidate()
    {
        Layout::invalidate();
        for (auto &widget : m_widgets)
        {
            widget->invalidate();
        }
    }

    ///////////////////////////////////////////////////////////////

    void LinearLayout::compact()
    {
        Layout::compact();
        if (m_widgets.size() > 0)
        {
            sf::Vector2f size(0, 0);
            switch (m_orientation)
            {
            case Horizontal:
                for (auto &widget : m_widgets)
                {
                    widget->compact();
                    size.x += widget->getWidth();
                    size.y = std::max(size.y, widget->getHeight());
                }
                break;

            case Vertical:
                for (auto &widget : m_widgets)
                {
                    widget->compact();
                    size.y += widget->getHeight();
                    size.x = std::max(size.x, widget->getWidth());
                }
                break;
            }
            setWidth(std::max(getWidth(), size.x + getHorizontalSpacing()));
            setHeight(std::max(getHeight(), size.y + getVerticalSpacing()));
        }
    }

    void LinearLayout::inflate(const Box &box)
    {
        Layout::inflate(box);
        if (m_widgets.size() > 0)
        {
            f32t offset = 0;
            switch (m_orientation)
            {
            case Horizontal:
            {
                auto innerHeight = getInnerHeight();
                for (auto &widget : m_widgets)
                {
                    auto width = widget->getWidth();
                    widget->inflate(Box(offset, 0, width, innerHeight));
                    offset += width;
                }
            }
            break;
            case Vertical:
            {
                auto innerWidth = getInnerWidth();
                for (auto &widget : m_widgets)
                {
                    auto height = widget->getHeight();
                    widget->inflate(Box(0, offset, innerWidth, height));
                    offset += height;
                }
            }
            break;
            }
        }
    }

    LinearLayout::LinearLayout()
        : m_widgets(), m_orientation(Horizontal) {}

    LinearLayout::~LinearLayout() {}

    //////////////////////////////////////////////////////////////

    void LinearLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Layout::onDraw(target, states);
        if (m_widgets.size() > 0)
        {
            auto _states = states;
            auto &padding = getPadding();
            _states.transform.translate({padding.left, padding.top});
            for (auto &widget : m_widgets)
            {
                target.draw(*widget, _states);
            }
        }
    }

    void LinearLayout::onAttach(const SharedWidget &widget)
    {
        Layout::onAttach(widget);
        m_widgets.push_back(widget);
    }

    void LinearLayout::onDetach(const SharedWidget &widget)
    {
        Layout::onDetach(widget);
        m_widgets.remove(widget);
    }

}