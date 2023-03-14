#ifndef COLIB_SPAN_HPP
#define COLIB_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Span : public Widget
    {

    public:
        sf::Text &getText();
        const sf::Text &getText() const;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        Span();
        virtual ~Span();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;

    private:
        sf::Text m_text;
    };

}

#endif // COLIB_SPAN_HPP