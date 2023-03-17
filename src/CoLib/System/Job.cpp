#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    Job::State Job::getState() const
    {
        return m_state;
    }

    SharedDispatcher Job::getDispatcher() const
    {
        return m_dispatcher.lock();
    }

    /////////////////////////////////////////////////////////////

    void Job::run()
    {
        m_monitor.lock();
        if (m_state != Ready)
        {
            m_monitor.unlock();
            throw InvalidOperationException();
        }
        m_state = Running;
        m_monitor.unlock();
        try
        {
            onRun();
            m_monitor.lock();
            if (m_state == Running)
            {
                m_state = Done;
                m_waiter.unlock();
            }
            m_monitor.unlock();
        }
        catch (...)
        {
            m_monitor.lock();
            if (m_state == Running)
            {
                m_state = Error;
                m_waiter.unlock();
            }
            m_monitor.unlock();
        }
    }

    void Job::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    void Job::cancel()
    {
        m_monitor.lock();
        if (m_state != Running)
        {
            m_state = Canceled;
            m_waiter.unlock();
        }
        else
        {
            m_state = Canceled;
        }
        m_monitor.unlock();
    }

    Job::Job(State state)
        : m_monitor(), m_waiter(),
          m_state(state), m_dispatcher()
    {
        if (m_state == Ready)
        {
            m_waiter.lock();
        }
    }

    Job::~Job()
    {
        cancel();
    }

    ///////////////////////////////////////////////////////////////////

    void Job::attach(const SharedDispatcher &dispatcher)
    {
        if (getDispatcher() != nullptr)
        {
            throw InvalidOperationException(JOB_ALREADY_ATTACHED_MESSAGE);
        }
        m_dispatcher = dispatcher;
    }

    void Job::detach()
    {
        if (getDispatcher() == nullptr)
        {
            throw InvalidOperationException(JOB_ALREADY_DETACHED_MESSAGE);
        }
        m_dispatcher.reset();
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