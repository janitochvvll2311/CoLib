#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    JobImpl::State JobImpl::getState() const
    {
        return m_state;
    }

    void JobImpl::run()
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

    void JobImpl::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    void JobImpl::cancel()
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

    JobImpl::~JobImpl()
    {
        cancel();
    }

    ///////////////////////////////////////////////////

    JobImpl::JobImpl(State state)
        : m_monitor(),
          m_waiter(),
          m_state(state)
    {
        if (m_state == Ready)
        {
            m_waiter.lock();
        }
    }

}