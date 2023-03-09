#include <algorithm>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    bool Dispatcher::attach(const SharedJob &job)
    {
        m_mutex.lock();
        if (std::find(m_jobs.begin(), m_jobs.end(), job) != m_jobs.end())
        {
            m_mutex.unlock();
            return false;
        }
        m_jobs.push_back(job);
        if (m_jobs.size() == 1)
        {
            m_waiter.unlock();
        }
        m_mutex.unlock();
        return true;
    }

    bool Dispatcher::detach(const SharedJob &job)
    {
        m_mutex.lock();
        if (std::find(m_jobs.begin(), m_jobs.end(), job) == m_jobs.end())
        {
            m_mutex.unlock();
            return false;
        }
        m_jobs.remove(job);
        if (m_jobs.size() == 0)
        {
            m_waiter.lock();
        }
        m_mutex.unlock();
        return true;
    }

    SharedJob Dispatcher::take()
    {
        m_mutex.lock();
        SharedJob job(nullptr);
        if (m_jobs.size() > 0)
        {
            job = m_jobs.front();
            m_jobs.pop_front();
        }
        m_mutex.unlock();
        return job;
    }

    void Dispatcher::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    Dispatcher::Dispatcher()
        : m_mutex(),
          m_waiter(),
          m_jobs()
    {
        m_waiter.lock();
    }

    Dispatcher::~Dispatcher()
    {
        m_mutex.lock();
        if (m_jobs.size() == 0)
        {
            m_waiter.unlock();
        }
        else
        {
            m_jobs.clear();
        }
        m_mutex.unlock();
    }

    ////////////////////////////////////////////////////////////////

    void runWorker(const WeakDispatcher &dispatcher)
    {
        while (!dispatcher.expired())
        {
            auto _dispatcher = dispatcher.lock();
            if (_dispatcher != nullptr)
            {
                _dispatcher->wait();
                auto job = _dispatcher->take();
                if (job)
                {
                    try
                    {
                        (*job)();
                    }
                    catch (...)
                    {
                    }
                }
            }
        }
    }

    ////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const SharedDispatcher Main(new Dispatcher());
    }
}