#ifndef COLIB_BUTTON_HPP
#define COLIB_BUTTON_HPP

#include <CoLib/UI/Label.hpp>
#include <CoLib/UI/Focusable.hpp>
#include <CoLib/UI/Clickable.hpp>

namespace co
{

    class COLIB_UI_API Button
        : public Label,
          public virtual Focusable,
          public virtual Clickable
    {
    public:
        const EventListener &getOnClickListener() const;
        void setOnClickListener(const EventListener &value);

        bool handleEvent(Node *target, const sf::Event &event) override;

        Button();
        virtual ~Button();

    protected:
        void onFocus(const sf::Event &event) override;
        void onClick(const sf::Event &event) override;

    private:
        bool m_focused;
        EventListener m_onClick;
    };

}

#endif // COLIB_BUTTON_HPP