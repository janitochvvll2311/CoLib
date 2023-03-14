#ifndef COLIB_LAYOUT_HPP
#define COLIB_LAYOUT_HPP

#include <memory>
#include <CoLib/UI/Widget.hpp>

namespace co
{

    using SharedWidget = std::shared_ptr<Widget>;

    //////////////////////////////////////////////

    class COLIB_UI_API Layout
    {

    public:
        void attach(const SharedWidget &widget);
        void detach(const SharedWidget &widget);

        Layout();
        virtual ~Layout();

        static const SharedWidget NoWidget;

    protected:
        virtual void onAttach(const SharedWidget &widget);
        virtual void onDetach(const SharedWidget &widget);
    };

}

#endif // COLIB_LAYOUT_HPP