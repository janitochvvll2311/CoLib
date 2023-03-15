#ifndef COLIB_CLICKABLE_HPP
#define COLIB_CLICKABLE_HPP

#include <SFML/Window/Mouse.hpp>
#include <CoLib/UI/Export.hpp>

namespace sf
{
    class Event;
}

namespace co
{

    class COLIB_UI_API Clickable
    {

    public:
        void click(sf::Mouse::Button button = sf::Mouse::Left, f32t x = 0, f32t y = 0);

        Clickable();
        virtual ~Clickable();

    protected:
        virtual void onClick(const sf::Event &event) = 0;
    };

}

#endif // COLIB_CLICKABLE_HPP