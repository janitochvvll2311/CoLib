#ifndef COLIB_INPUT_HPP
#define COLIB_INPUT_HPP

#include <CoLib/UI/Label.hpp>
#include <CoLib/UI/Focusable.hpp>

namespace co
{

    class COLIB_UI_API Input
        : public Label,
          public virtual Focusable
    {

    public:
        bool handleEvent(Widget *target, const sf::Event &event) override;

        Input();
        virtual ~Input();

    protected:
        void onFocus(const sf::Event &event) override;
    };

}

#endif // COLIB_INPUT_HPP