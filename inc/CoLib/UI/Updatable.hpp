#ifndef COLIB_UPDATABLE_HPP
#define COLIB_UPDATABLE_HPP

#include <CoLib/UI/Export.hpp>

namespace co
{

    class COLIB_UI_API Updatable
    {

    public:
        virtual bool isValid() const = 0;
        virtual void invalidate() = 0;
        void update(bool force = false) const;

        Updatable();
        virtual ~Updatable();

    protected:
        virtual void onUpdate() const = 0;
    };

}

#endif // COLIB_UPDATABLE_HPP