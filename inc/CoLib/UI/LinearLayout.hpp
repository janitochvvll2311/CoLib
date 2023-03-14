#ifndef COLIB_LINEAR_LAYOUT_HPP
#define COLIB_LINEAR_LAYOUT_HPP

#include <list>
#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>
#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    class COLIB_UI_API LinearLayout
        : public Block,
          public virtual Layout
    {

    public:
        enum Alignment
        {
            Start,
            Center,
            End
        };

        Alignment getAlignment(const SharedWidget &widget) const;
        void setAlignment(const SharedWidget &widget, Alignment value);

        //////////////////////////////////////////////////////////////

        bool isValid() const override;
        void invalidate() override;

        void compact() override;
        void inflate(const sf::Vector2f &size) override;

        LinearLayout();
        virtual ~LinearLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        class WidgetHolder;
        using SharedHolder = std::shared_ptr<WidgetHolder>;

        ////////////////////////////////////////////////////////////

        class WidgetHolder : public co::WidgetHolder
        {
        public:
            Alignment getAlignment() const;
            void setAlignment(Alignment value);

            WidgetHolder();
            virtual ~WidgetHolder();

        private:
            Alignment m_alignment;
        };

        //////////////////////////////////////////////////////////////

        SharedHolder getHolder(const SharedWidget &widget) const;

        std::list<SharedHolder> m_holders;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP