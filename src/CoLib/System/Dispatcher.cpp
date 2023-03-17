#include <algorithm>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Utils.hpp>
#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    void Dispatcher::append(const SharedJob &job)
    {
        auto instance = getInstance();
        auto manager = Job::Manager(job);
        manager.attach(instance);
        //
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
        auto instace = getInstance();
        if (job->getDispatcher() != instace)
        {
            throw InvalidOperationException(JOB_ALREADY_ATTACHED_MESSAGE);
        }
        auto monitor = Job::Manager(job);
        monitor.detach();
        //
        m_monitor.lock();
        m_jobs.remove(job);
        if (m_jobs.size() == 0)
        {
            m_waiter.lock();
        }
        m_monitor.unlock();
    }

    SharedJob Dispatcher::take()
    {
        m_monitor.lock();
        SharedJob job(nullptr);
        if (m_jobs.size() > 0)
        {
            job = m_jobs.front();
            m_jobs.pop_front();
            if (m_jobs.size() == 0)
            {
                m_waiter.lock();
            }
        }
        m_monitor.unlock();
        return job;
    }

    void Dispatcher::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    Dispatcher::Dispatcher()
        : m_monitor(),
          m_waiter(),
          m_jobs()
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

    ////////////////////////////////////////////////////////////////

    SharedDispatcher Dispatcher::getInstance()
    {
        auto instance = cast<Dispatcher>();
        if (!instance)
        {
            throw InvalidStateException(UNSAFE_OBJECT_INSTANCE_MESSAGE);
        }
        return instance;
    }

    ////////////////////////////////////////////////////////////////

    void runWorker(
        const WeakDispatcher &dispatcher,
        const std::function<void(const Exception &)> &handler)
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

    ////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const SharedDispatcher Main = Object::create<Dispatcher>();
    }
}