#ifndef COLIB_JOB_INL
#define COLIB_JOB_INL

#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    Job::State Job::getState() const { return m_state; }

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
            m_job();
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

    Job::Job(const std::function<void()> &job)
        : m_monitor(),
          m_waiter(),
          m_state(Empty),
          m_job(job)
    {
        if (m_job)
        {
            m_state = Ready;
            m_waiter.lock();
        }
    }

    Job::~Job()
    {
        cancel();
    }

}

#endif // COLIB_JOB_INL