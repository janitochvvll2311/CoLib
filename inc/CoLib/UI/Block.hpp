#ifndef COLIB_BLOCK_HPP
#define COLIB_BLOCK_HPP

#include <CoLib/UI/Thickness.hpp>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    class Background;
    using SharedBackground = std::shared_ptr<Background>;

    //////////////////////////////////////////////////

    class COLIB_UI_API Block : public Widget
    {

    public:
        const SharedBackground &getBackground() const;
        void setBackground(const SharedBackground &value);

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        void compact() override;
        void inflate(const sf::Vector2f &size, const Aligner *const aligner = nullptr) override;

        Block();
        ~Block();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable SharedBackground m_background;

        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;
        Thickness m_margin;
    };

}

#endif // COLIB_BLOCK_HPP