#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    inline void Task<void>::start(const SharedDispatcher &dispatcher)
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        dispatcher->append(m_job);
    }

    inline void Task<void>::wait() const
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        auto dispatcher = m_job->getDispatcher();
        if (!dispatcher || dispatcher->tryRemove(m_job))
        {
            m_job->run();
        }
    }

    inline void Task<void>::cancel()
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        m_job->cancel();
    }

    inline Task<void>::Task(const std::function<void()> &task)
        : m_job()
    {
        if (task)
        {
            m_job.reset(new Job(task));
        }
    }

    inline Task<void>::~Task() {}

    inline Task<void>::Job::Job(const std::function<void()> &job)
        : co::Job(job ? Ready : Empty), m_job(job) {}

    inline Task<void>::Job::~Job() {}

    inline void Task<void>::Job::onRun()
    {
        m_job();
    }

    ///////////////////////////////////////////////////////////////////

    template <typename T>
    inline const Optional<T> &Task<T>::getResult() const
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        return m_job->getResult();
    }

    template <typename T>
    inline void Task<T>::start(const SharedDispatcher &dispatcher)
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        dispatcher->append(m_job);
    }

    template <typename T>
    inline void Task<T>::wait() const
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        auto dispatcher = m_job->getDispatcher();
        if (!dispatcher || dispatcher->tryRemove(m_job))
        {
            m_job->run();
        }
    }

    template <typename T>
    inline void Task<T>::cancel()
    {
        if (!m_job)
        {
            throw InvalidOperationException();
        }
        m_job->cancel();
    }

    template <typename T>
    inline Task<T>::Task(const std::function<T()> &task)
        : m_job()
    {
        if (task)
        {
            m_job.reset(new Job(task));
        }
    }

    template <typename T>
    inline Task<T>::~Task() {}

    template <typename T>
    inline const Optional<T> &Task<T>::Job::getResult() const
    {
        return m_result;
    }

    template <typename T>
    inline Task<T>::Job::Job(const std::function<T()> &job)
        : co::Job(job ? Ready : Empty), m_job(job) {}

    template <typename T>
    inline Task<T>::Job::~Job() {}

    template <typename T>
    inline void Task<T>::Job::onRun()
    {
        m_result = m_job();
    }

}