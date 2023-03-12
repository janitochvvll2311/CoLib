#ifndef COLIB_ALIGNER_HPP
#define COLIB_ALIGNER_HPP

#include <CoLib/Config.hpp>

namespace co
{

    class Box;

    //////////////////////////////

    class Aligner
    {
    public:
        virtual void align(Box &box) const = 0;
        Aligner() = default;
        virtual ~Aligner() = default;
    };

}

#endif // COLIB_ALIGNER_HPP