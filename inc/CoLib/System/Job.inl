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
        : Job<void>(
              [=]()
              {
                  auto _job = job;
                  m_result = _job();
              }) {}

}

#endif // COLIB_JOB_INL