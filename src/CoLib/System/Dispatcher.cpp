#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    void Dispatcher::append(const SharedJob &job)
    {
        job->attach(this);
        m_monitor.lock();
        m_jobs.push_back(job);
        if (m_jobs.size() == 1)
        {
            m_waiter.unlock();
        }
        m_monitor.unlock();
    }

    void Dispatcher::remove(const SharedJob &job)
    {
        m_monitor.lock();
        if (job->getDispatcher() != this)
        {
            m_monitor.unlock();
            throw InvalidOperationException(JOB_ALREADY_ATTACHED_STRING);
        }
        job->detach();
        m_jobs.remove(job);
        if (m_jobs.size() == 0)
        {
            m_waiter.lock();
        }
        m_monitor.unlock();
    }

    bool Dispatcher::tryRemove(const SharedJob &job)
    {
        try
        {
            remove(job);
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    SharedJob Dispatcher::take()
    {
        m_monitor.lock();
        SharedJob job(nullptr);
        if (m_jobs.size() > 0)
        {
            job = m_jobs.front();
            m_jobs.pop_front();
            job->detach();
            if (m_jobs.size() == 0)
            {
                m_waiter.lock();
            }
        }
        m_monitor.unlock();
        return job;
    }

    SharedJob Dispatcher::wait()
    {
        m_waiter.lock();
        m_monitor.lock();
        SharedJob job(nullptr);
        if (m_jobs.size() > 0)
        {
            job = m_jobs.front();
            m_jobs.pop_front();
            job->detach();
            if (m_jobs.size() > 0)
            {
                m_waiter.unlock();
            }
        }
        m_monitor.unlock();
        return job;
    }

    Dispatcher::Dispatcher()
        : m_monitor(), m_waiter(), m_jobs()
    {
        m_waiter.lock();
    }

    Dispatcher::~Dispatcher()
    {
        m_monitor.lock();
        if (m_jobs.size() == 0)
        {
            m_waiter.unlock();
        }
        else
        {
            m_jobs.clear();
        }
        m_monitor.unlock();
    }

    const SharedDispatcher Dispatcher::Main = std::make_shared<Dispatcher>();

    //////////////////////////////////////////////////////////////////////////

    void runWorker(
        const WeakDispatcher &dispatcher,
        const ExceptionHandler &handler)
    {
        while (!dispatcher.expired())
        {
            auto _dispatcher = dispatcher.lock();
            if (_dispatcher != nullptr)
            {
                auto job = _dispatcher->wait();
                if (job)
                {
                    runCatching(
                        [&]()
                        {
                            job->run();
                        },
                        handler);
                }
            }
        }
    }

}