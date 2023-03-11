#ifndef COLIB_LAYOUT_HPP
#define COLIB_LAYOUT_HPP

#include <CoLib/UI/Widget.hpp>

namespace co
{

    using SharedWidget = std::shared_ptr<Widget>;

    //////////////////////////////////////////////

    class COLIB_UI_API Layout : public Widget
    {

    public:
        const Thickness &getPadding() const;
        void setPadding(const Thickness &value);

        f32t getInnerWidth() const;
        f32t getInnerHeight() const;

        ////////////////////////////////////////////////////

        f32t getHorizontalSpacing() const override;
        f32t getVerticalSpacing() const override;

        void attach(const SharedWidget &widget);
        void detach(const SharedWidget &widget);

        Layout();
        ~Layout();

    protected:
        virtual void onAttach(const SharedWidget &widget);
        virtual void onDetach(const SharedWidget &widget);

    private:
        Thickness m_padding;
    };

}

#endif // COLIB_LAYOUT_HPP