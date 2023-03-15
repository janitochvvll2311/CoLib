#include <CoLib/UI/WidgetHolder.hpp>

namespace co
{

    const SharedWidget &WidgetHolder::getWidget() const
    {
        return m_widget;
    }

    void WidgetHolder::setWidget(const SharedWidget &value)
    {
        m_widget = value;
    }

    WidgetHolder::WidgetHolder()
        : m_widget(nullptr) {}

    WidgetHolder::~WidgetHolder() {}

}