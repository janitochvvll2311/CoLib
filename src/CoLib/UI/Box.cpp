#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Box.hpp>

namespace co
{

    f32t Box::getLeft() const
    {
        return m_left;
    }

    void Box::setLeft(f32t value, bool expand)
    {
        if (expand)
        {
            m_width += m_left - value;
        }
        m_left = value;
    }

    f32t Box::getRight() const
    {
        return m_left + m_width;
    }

    void Box::setRight(f32t value, bool expand)
    {
        if (expand)
        {
            m_width = value - m_left;
        }
        m_left = value - m_width;
    }

    f32t Box::getTop() const
    {
        return m_top;
    }

    void Box::setTop(f32t value, bool expand)
    {
        if (expand)
        {
            m_height += m_top - value;
        }
        m_top = value;
    }

    f32t Box::getBottom() const
    {
        return m_top + m_height;
    }

    void Box::setBottom(f32t value, bool expand)
    {
        if (expand)
        {
            m_height = value - m_top;
        }
        m_top = value - m_height;
    }

    f32t Box::getWidth() const
    {
        return m_width;
    }

    void Box::setWidth(f32t value, Alignment alignment)
    {
        switch (alignment)
        {
        case Start:
            break;
        case End:
            m_left -= value - m_width;
            break;
        case Center:
            m_left -= (value - m_width) / 2;
            break;
        }
        m_width = value;
    }

    f32t Box::getHeight() const
    {
        return m_height;
    }

    void Box::setHeight(f32t value, Alignment alignment)
    {
        switch (alignment)
        {
        case Start:
            break;
        case End:
            m_top -= value - m_height;
            break;
        case Center:
            m_top -= (value - m_height) / 2;
            break;
        }
        m_height = value;
    }

    void Box::shrink(const Thickness &thickness)
    {
        m_left += thickness.left;
        m_top += thickness.top;
        m_width -= thickness.getHorizontal();
        m_height -= thickness.getVertical();
    }

    void Box::expand(const Thickness &thickness)
    {
        m_left -= thickness.left;
        m_top -= thickness.top;
        m_width += thickness.getHorizontal();
        m_height += thickness.getVertical();
    }

    void Box::alignHorizontal(const Box &box, Alignment alignment)
    {
        switch (alignment)
        {
        case Start:
            m_left = box.m_left;
            break;
        case End:
            m_left = box.m_left + box.m_width - m_width;
            break;
        case Center:
            m_left = box.m_left + (box.m_width - m_width) / 2;
            break;
        }
    }

    void Box::alignVertical(const Box &box, Alignment alignment)
    {
        switch (alignment)
        {
        case Start:
            m_top = box.m_top;
            break;
        case End:
            m_top = box.m_top + box.m_height - m_height;
            break;
        case Center:
            m_top = box.m_top + (box.m_height - m_height) / 2;
            break;
        }
    }

    Box::Box(f32t width, f32t height)
        : m_left(0), m_top(0), m_width(width), m_height(height) {}

    Box::Box(f32t left, f32t top, f32t width, f32t height)
        : m_left(left), m_top(top), m_width(width), m_height(height) {}

    Box::~Box() {}

}