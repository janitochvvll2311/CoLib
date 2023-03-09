#include <CoLib/UI/Thickness.hpp>

namespace co
{

    f32t Thickness::getHorizontal() const
    {
        return left + right;
    }

    f32t Thickness::getVertical() const
    {
        return top + bottom;
    }

    Thickness::Thickness(f32t value)
        : left(value), top(value), right(value), bottom(value) {}

    Thickness::Thickness(f32t horizontal, f32t vertical)
        : left(horizontal), top(vertical), right(horizontal), bottom(vertical) {}

    Thickness::Thickness(f32t _left, f32t _top, f32t _right, f32t _bottom)
        : left(_left), top(_top), right(_right), bottom(_bottom) {}

}