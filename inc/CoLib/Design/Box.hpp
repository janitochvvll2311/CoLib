#ifndef COLIB_BOX_HPP
#define COLIB_BOX_HPP

#include <CoLib/Design/Export.hpp>

namespace co
{

    class COLIB_DESIGN_API Box
    {

    public:
        enum Gravity
        {
            Start,
            End,
            Center
        };

        f32t getLeft() const;
        void setLeft(f32t value, bool expand = false);

        f32t getRight() const;
        void setRight(f32t value, bool expand = false);

        f32t getTop() const;
        void setTop(f32t value, bool expand = false);

        f32t getBottom() const;
        void setBottom(f32t value, bool expand = false);

        f32t getWidth() const;
        void setWidth(f32t value, Gravity gravity = Start);

        f32t getHeight() const;
        void setHeight(f32t value, Gravity gravity = Start);

        Box(f32t width = 0, f32t height = 0);
        Box(f32t left, f32t top, f32t width, f32t height);
        ~Box();

    private:
        f32t m_left;
        f32t m_top;
        f32t m_width;
        f32t m_height;
    };

}

#endif // COLIB_BOX_HPP