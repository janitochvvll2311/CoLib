#ifndef COLIB_BACKGROUND_HPP
#define COLIB_BACKGROUND_HPP

#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Background
        : public Widget
    {

    public:
        const sf::Color &getColor() const;
        void setColor(const sf::Color &value);

        Background();
        ~Background();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable Graph m_background;
    };

}

#endif // COLIB_BACKGROUND_HPP