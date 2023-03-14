#ifndef COLIB_WIDGET_HOLDER_HPP
#define COLIB_WIDGET_HOLDER_HPP

#include <memory>
#include <CoLib/UI/Export.hpp>

namespace co
{

    class Widget;
    using SharedWidget = std::shared_ptr<Widget>;

    class COLIB_UI_API WidgetHolder
    {

    public:
        const SharedWidget &getWidget() const;
        void setWidget(const SharedWidget &value);

        WidgetHolder();
        virtual ~WidgetHolder();

    private:
        SharedWidget m_widget;
    };

}

#endif // COLIB_WIDGET_HOLDER_HPP