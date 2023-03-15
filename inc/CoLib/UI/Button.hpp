#ifndef COLIB_BUTTON_HPP
#define COLIB_BUTTON_HPP

#include <CoLib/UI/Label.hpp>

namespace co
{

    class COLIB_UI_API Button : public Label
    {

    public:
        const EventListener &getOnClickListener() const;
        void setOnClickListener(const EventListener &value);

        bool handleEvent(Widget *target, const sf::Event &event) override;
        void click(sf::Mouse::Button button = sf::Mouse::Left, f32t x = 0, f32t y = 0);

        Button();
        virtual ~Button();

    protected:
        virtual void onClick(const sf::Event &event);

    private:
        EventListener m_onClick;
    };

}

#endif // COLIB_BUTTON_HPP