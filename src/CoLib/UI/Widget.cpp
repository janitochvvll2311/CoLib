#include <math.h>
#include <limits>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    const Graph *const Widget::getBackground() const
    {
        return m_background.get();
    }

    void Widget::setBackground(const Graph &value)
    {
        m_background.reset(new Graph(value));
    }

    /////////////////////////////////////////////////////////////

    f32t Widget::getMinWidth() const
    {
        return m_minWidth;
    }

    void Widget::setMinWidth(f32t value)
    {
        m_minWidth = value;
    }

    f32t Widget::getMaxWidth() const
    {
        return m_maxWidth;
    }

    void Widget::setMaxWidth(f32t value)
    {
        m_maxWidth = value;
    }

    f32t Widget::getMinHeight() const
    {
        return m_minHeight;
    }

    void Widget::setMinHeight(f32t value)
    {
        m_minHeight = value;
    }

    f32t Widget::getMaxHeight() const
    {
        return m_maxHeight;
    }

    void Widget::setMaxHeight(f32t value)
    {
        m_maxHeight = value;
    }

    ////////////////////////////////////////////////////////////////

    const Thickness &Widget::getMargin() const
    {
        return m_margin;
    }

    void Widget::setMargin(const Thickness &value)
    {
        m_margin = value;
    }

    f32t Widget::getHorizontalSpacing() const
    {
        return m_margin.getHorizontal();
    }

    f32t Widget::getVerticalSpacing() const
    {
        return m_margin.getVertical();
    }

    Widget::Alignment Widget::getHorizontalAlignment() const
    {
        return m_hAlignment;
    }

    void Widget::setHorizontalAlignment(Alignment value)
    {
        m_hAlignment = value;
    }

    Widget::Alignment Widget::getVerticalAlignment() const
    {
        return m_vAlignment;
    }

    void Widget::setVerticalAlignment(Alignment value)
    {
        m_vAlignment = value;
    }

    ////////////////////////////////////////////////////////////////

    bool Widget::isValid() const
    {
        return m_isValid;
    }

    void Widget::invalidate()
    {
        m_isValid = false;
    }

    void Widget::compact(const sf::Vector2f &size)
    {
        setWidth(std::min(std::max(m_minWidth + getHorizontalSpacing(), size.x), m_maxWidth));
        setHeight(std::min(std::max(m_minHeight + getVerticalSpacing(), size.y), m_maxHeight));
    }

    void Widget::inflate(const Box &box)
    {
        compact({std::max(getWidth(), box.getWidth()), std::max(getHeight(), box.getHeight())});
        alignHorizontal(box, m_hAlignment);
        alignVertical(box, m_vAlignment);
        shrink(m_margin);
    }

    Widget::Widget()
        : Box(),
          m_isValid(false), m_background(nullptr),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_margin(0), m_hAlignment(Start), m_vAlignment(Start),
          m_parent(nullptr)
    {
    }

    Widget::~Widget() {}

    ///////////////////////////////////////////////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (!m_isValid)
        {
            onUpdate(m_background);
            m_isValid = true;
        }
        auto _states = states;
        _states.transform.translate({getLeft(), getTop()});
        _states.transform.combine(getTransform());
        onDraw(target, _states);
    }

    void Widget::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_background && getWidth() > 0 && getHeight() > 0)
        {
            target.draw(*m_background, states);
        }
    }

    void Widget::onUpdate(const UniqueGraph &background) const
    {
        if (background && getWidth() > 0 && getHeight() > 0)
        {
            background->fitPoints({{0, 0}, {getWidth(), getHeight()}});
        }
    }

}