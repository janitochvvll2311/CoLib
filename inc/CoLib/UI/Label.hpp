#ifndef COLIB_LABEL_HPP
#define COLIB_LABEL_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class Span;

    ///////////////////////////////////////////////////////

    class COLIB_UI_API Label : public Widget
    {

    public:
        using Alignment = FrameLayout::Alignment;

        Alignment getHorizontalContentAlignment() const;
        void setHorizontalContentAlignment(Alignment value);

        Alignment getVerticalContentAlignment() const;
        void setVerticalContentAlignment(Alignment value);

        Block &getBlock();
        const Block &getBlock() const;

        Span &getSpan();
        const Span &getSpan() const;

        /////////////////////////////////////////////

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        Label();
        virtual ~Label();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        FrameLayout m_root;
    };

}

#endif // COLIB_LABEL_HPP