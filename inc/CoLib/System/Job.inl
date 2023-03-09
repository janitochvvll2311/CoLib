#ifndef COLIB_JOB_INL
#define COLIB_JOB_INL

#include <CoLib/System/Job.hpp>

namespace co
{

    template <typename T>
    inline const T &Job<T>::getResult() const
    {
        return m_result;
    }

    template <typename T>
    inline Job<T>::Job(const std::function<T()> &job)
        : JobImpl(job ? Ready : Empty),
          m_job(job) {}

    template <typename T>
    inline void Job<T>::onRun()
    {
        m_result = m_job();
    }

    //////////////////////////////////////////////////////////

    inline Job<void>::Job(const std::function<void()> &job)
        : JobImpl(job ? Ready : Empty),
          m_job(job) {}

    inline void Job<void>::onRun()
    {
        m_job();
    }

}

#endif // COLIB_JOB_INL