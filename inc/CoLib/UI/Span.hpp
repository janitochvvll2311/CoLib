#ifndef COLIB_SPAN_HPP
#define COLIB_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Span : public Widget
    {

    public:
        const sf::Text &getText() const;
        void setText(const sf::Text &value);

        void compact(const sf::Vector2f& size) override;
        void inflate(const Box &box) override;

        Span();
        ~Span();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Text m_text;
    };

}

#endif // COLIB_SPAN_HPP