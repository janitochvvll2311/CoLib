#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    void TaskImpl::start(const SharedDispatcher &dispatcher)
    {
        if (m_job->getState() != JobImpl::Ready)
        {
            throw InvalidJobStateException();
        }
        dispatcher->attach(m_job);
    }

    void TaskImpl::wait() const
    {
        if (m_job->getState() == JobImpl::Ready)
        {
            auto dispatcher = m_job->getDispatcher();
            if (!dispatcher || dispatcher->detach(m_job))
            {
                m_job->run();
            }
        }
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