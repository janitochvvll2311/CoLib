#ifndef COLIB_BACKGROUND_HPP
#define COLIB_BACKGROUND_HPP

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <CoLib/Config.hpp>

namespace co
{

    class Background : public virtual sf::Drawable
    {
    public:
        virtual void setBounds(const sf::FloatRect &bounds) = 0;
        Background() = default;
        ~Background() = default;
    };

}

#endif // COLIB_BACKGROUND_HPP