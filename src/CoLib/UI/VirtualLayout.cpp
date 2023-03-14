#include <CoLib/UI/VirtualLayout.hpp>

namespace co
{

    void VirtualLayout::compact()
    {
        FrameLayout::compact();
        Block::compact();
    }

    VirtualLayout::VirtualLayout() {}

    VirtualLayout::~VirtualLayout() {}

}