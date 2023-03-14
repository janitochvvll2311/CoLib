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
        class LinearWidgetHolder : public WidgetHolder
        {
        public:
            LinearWidgetHolder();
            virtual ~LinearWidgetHolder();
        };

        std::list<std::shared_ptr<LinearWidgetHolder>> m_holders;
    };

}

#endif // COLIB_LINEAR_LAYOUT_HPP