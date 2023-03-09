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

    void Widget::compact()
    {
        setWidth(m_minWidth + getHorizontalSpacing());
        setHeight(m_minHeight + getVerticalSpacing());
    }

    void Widget::inflate(const Box &box)
    {
        auto _box = box;
        _box.shrink(m_margin);
        setWidth(std::min(std::max(m_minWidth, _box.getWidth()), m_maxWidth));
        setHeight(std::min(std::max(m_minHeight, _box.getHeight()), m_maxHeight));
        alignHorizontal(_box, m_hAlignment);
        alignVertical(_box, m_vAlignment);
    }

    Widget::Widget()
        : Box(),
          m_isValid(false), m_background(nullptr),
          m_minWidth(0), m_maxWidth(std::numeric_limits<f32t>::infinity()),
          m_minHeight(0), m_maxHeight(std::numeric_limits<f32t>::infinity()),
          m_margin(0), m_hAlignment(Start), m_vAlignment(Start)
    {
    }

    Widget::Widget(f32t width, f32t height)
        : Widget()
    {
        setWidth(m_minWidth = m_maxWidth = width);
        setHeight(m_minHeight = m_maxHeight = height);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////

    void Widget::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (!m_isValid)
        {
            onUpdate(m_background);
            m_isValid = true;
        }
        if (m_background)
        {
            auto _states = states;
            _states.transform.translate({getLeft(), getTop()});
            _states.transform.combine(getTransform());
            target.draw(*m_background, _states);
        }
    }

    void Widget::onUpdate(const UniqueGraph &background) const
    {
        if (background)
        {
            background->fitPoints({{0, 0}, {getWidth(), getHeight()}});
        }
    }

}