#define COLIB_UI_EXPORTS
#include <CoLib/UI/Updatable.hpp>

namespace co
{

    void Updatable::update(bool force) const
    {
        if (!isValid() || force)
        {
            onUpdate();
        }
    }

    Updatable::Updatable() {}
    Updatable::~Updatable() {}

}