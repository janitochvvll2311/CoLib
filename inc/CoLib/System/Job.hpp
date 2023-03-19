#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <CoLib/System/Export.hpp>

namespace co
{

    class Dispatcher;

    class COLIB_SYSTEM_API Job
    {
    public:
        virtual Dispatcher *getDispatcher() const = 0;

        void run();
        void attach(Dispatcher *dispatcher);
        void detach();

        Job();
        virtual ~Job();

    protected:
        virtual void onRun() = 0;
        virtual void onAttach(Dispatcher *dispatcher) = 0;
        virtual void onDetach() = 0;
    };

}

#endif // COLIB_JOB_HPP