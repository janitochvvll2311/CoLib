#include <CoLib/System/Task.hpp>

namespace co
{

    void TaskImpl::start(const SharedDispatcher &dispatcher)
    {
        dispatcher->attach(m_job);
    }

    void TaskImpl::wait() const
    {
        m_job->wait();
    }

    void TaskImpl::cancel()
    {
        m_job->cancel();
    }

    TaskImpl::~TaskImpl() {}

    ///////////////////////////////////////////

    TaskImpl::TaskImpl(const SharedJob &job)
        : m_job(job) {}

}