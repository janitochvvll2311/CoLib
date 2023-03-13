#ifndef COLIB_SPAN_HPP
#define COLIB_SPAN_HPP

#include <SFML/Graphics/Text.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class COLIB_UI_API Span : public Widget
    {

    public:
        const sf::String &getString() const;
        void setString(const sf::String &value);

        const sf::Font *getFont() const;
        void setFont(const sf::Font &font);

        f32t getCharacterSize() const;
        void setCharacterSize(f32t value);

        const sf::Color &getFillColor() const;
        void setFillColor(const sf::Color &value);

        sf::Uint32 getStyle() const;
        void setStyle(sf::Uint32 value);

        f32t getOutlineThickness() const;
        void setOutlineThickness(f32t value);

        const sf::Color &getOutlineColor() const;
        void setOutlineColor(const sf::Color &value);

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