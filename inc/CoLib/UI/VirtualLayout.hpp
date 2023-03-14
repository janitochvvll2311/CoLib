#ifndef COLIB_VIRTUAL_LAYOUT_HPP
#define COLIB_VIRTUAL_LAYOUT_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API VirtualLayout
        : public FrameLayout
    {

    public:
        void compact() override;

        VirtualLayout();
        virtual ~VirtualLayout();
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP