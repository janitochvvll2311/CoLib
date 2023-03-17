#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    Job::Job() {}
    Job::~Job() {}

    ///////////////////////////////////////////////////////////////////

    void Job::attach(const SharedDispatcher &dispatcher)
    {
        if (getDispatcher() != nullptr)
        {
            throw InvalidOperationException(JOB_ALREADY_ATTACHED_MESSAGE);
        }
        onAttach(dispatcher);
    }

    void Job::detach()
    {
        if (getDispatcher() == nullptr)
        {
            throw InvalidOperationException(JOB_ALREADY_DETACHED_MESSAGE);
        }
        onDetach();
    }

    ///////////////////////////////////////////////////////////////////

    void Job::Manager::attach(const SharedDispatcher &dispatcher)
    {
        m_job->attach(dispatcher);
    }

    void Job::Manager::detach()
    {
        m_job->detach();
    }

    Job::Manager::Manager(const SharedJob &job)
        : m_job(job) {}

    Job::Manager::~Manager() {}

}