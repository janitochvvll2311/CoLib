#ifndef COLIB_BUTTON_HPP
#define COLIB_BUTTON_HPP

#include <functional>
#include <CoLib/UI/Label.hpp>

namespace co
{

    class COLIB_UI_API Button : public Label
    {

    public:
        using OnClickListener = std::function<void(Widget &)>;

        const OnClickListener &getOnClickListener() const;
        void setOnClickListener(const OnClickListener &value);

        bool handleEvent(const sf::Event& event) override;

        Button();
        virtual ~Button();

    private:
        OnClickListener m_onClick;
    };

}

#endif // COLIB_BUTTON_HPP