#ifndef COLIB_WIDGET_HPP
#define COLIB_WIDGET_HPP

#include <memory>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <CoLib/UI/Box.hpp>
#include <CoLib/UI/Thickness.hpp>

namespace co
{

    class Layout;

    class Graph;
    using UniqueGraph = std::unique_ptr<Graph>;

    ///////////////////////////////////////////////////////

    class COLIB_UI_API Widget
        : public sf::Transformable,
          public Box,
          public virtual sf::Drawable
    {

        friend Layout;

    public:
        const Graph *const getBackground() const;
        void setBackground(const Graph &value);

        /////////////////////////////////////////////////

        f32t getMinWidth() const;
        void setMinWidth(f32t value);

        f32t getMaxWidth() const;
        void setMaxWidth(f32t value);

        f32t getMinHeight() const;
        void setMinHeight(f32t value);

        f32t getMaxHeight() const;
        void setMaxHeight(f32t value);

        /////////////////////////////////////////////////

        const Thickness &getMargin() const;
        void setMargin(const Thickness &value);

        virtual f32t getHorizontalSpacing() const;
        virtual f32t getVerticalSpacing() const;

        Alignment getHorizontalAlignment() const;
        void setHorizontalAlignment(Alignment value);

        Alignment getVerticalAlignment() const;
        void setVerticalAlignment(Alignment value);

        /////////////////////////////////////////////////

        virtual bool isValid() const;
        virtual void invalidate();

        virtual void compact();
        virtual void inflate(const Box &box);

        Widget();
        ~Widget();

    protected:
        void draw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        virtual void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const;
        virtual void onUpdate(const UniqueGraph &background) const;

    private:
        mutable bool m_isValid;
        mutable UniqueGraph m_background;

        f32t m_minWidth;
        f32t m_maxWidth;
        f32t m_minHeight;
        f32t m_maxHeight;

        Thickness m_margin;
        Alignment m_hAlignment;
        Alignment m_vAlignment;

        Layout *m_parent;
    };

}

#endif // COLIB_WIDGET_HPP