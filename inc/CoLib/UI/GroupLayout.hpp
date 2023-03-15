#ifndef COLIB_GROUP_LAYOUT_HPP
#define COLIB_GROUP_LAYOUT_HPP

#include <CoLib/UI/Block.hpp>
#include <CoLib/UI/Layout.hpp>

namespace co
{

    class COLIB_UI_API GroupLayout
        : public Block,
          public virtual Layout
    {

    public:
        GroupLayout();
        virtual ~GroupLayout();
    };

}

#endif // COLIB_GROUP_LAYOUT_HPP