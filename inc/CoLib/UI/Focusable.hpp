#ifndef COLIB_FOCUSABLE_HPP
#define COLIB_FOCUSABLE_HPP

#include <CoLib/UI/Export.hpp>

namespace sf
{
    class Event;
}

namespace co
{

    class COLIB_UI_API Focusable
    {

    public:
        void focus();

        Focusable();
        virtual ~Focusable();

    protected:
        virtual void onFocus(const sf::Event &event) = 0;
    };

}

#endif // COLIB_FOCUSABLE_HPP