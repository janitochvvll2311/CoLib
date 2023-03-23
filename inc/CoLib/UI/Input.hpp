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
        const EventListener &getOnTextEnteredListener() const;
        void setOnTextEnteredListener(const EventListener &value);

        bool handleEvent(Node *target, const sf::Event &event) override;

        void enterText(sf::Uint32 unicode);

        Input();
        virtual ~Input();

    protected:
        void onFocus(const sf::Event &event) override;
        virtual void onTextEntered(const sf::Event &event);

    private:
        bool m_focused;
        EventListener m_onTextEntered;
    };

}

#endif // COLIB_INPUT_HPP