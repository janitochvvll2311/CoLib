#ifndef COLIB_INPUT_HPP
#define COLIB_INPUT_HPP

#include <CoLib/UI/Label.hpp>

namespace co
{

    class COLIB_UI_API Input : public Label
    {

    public:
        bool handleEvent(const sf::Event &event) override;

        Input();
        virtual ~Input();
    };

}

#endif // COLIB_INPUT_HPP