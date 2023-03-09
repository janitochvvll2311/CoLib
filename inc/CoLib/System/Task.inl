#ifndef COLIB_TASK_INL
#define COLIB_TASK_INL

#include <CoLib/System/Task.hpp>

namespace co
{

    template <typename T>
    inline const Optional<T> &Task<T>::await() const
    {
        std::shared_ptr<Job<T>> job(m_job);
        job->wait();
        return job->getResult();
    }

    template <typename T>
    inline Task<T>::Task(const std::function<T()> &job)
        : TaskImpl(std::make_shared<Job<T>>(job)) {}

    /////////////////////////////////////////////////////////////////

    inline Task<void>::Task(const std::function<void()> &job)
        : TaskImpl(std::make_shared<Job<void>>(job)) {}

}

#endif // COLIB_TASK_INL