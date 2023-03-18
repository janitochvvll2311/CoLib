#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    void Job::run()
    {
        if (getDispatcher())
        {
            throw InvalidOperationException(JOB_STILL_ATTACHED_STRING);
        }
        onRun();
    }

    void Job::attach(Dispatcher *dispatcher)
    {
        if (getDispatcher())
        {
            throw InvalidOperationException(JOB_ALREADY_ATTACHED_STRING);
        }
        onAttach(dispatcher);
    }

    void Job::detach()
    {
        if (!getDispatcher())
        {
            throw InvalidOperationException(JOB_ALREADY_DETACHED_STRING);
        }
        onDetach();
    }

    Job::Job() {}
    Job::~Job() {}

}