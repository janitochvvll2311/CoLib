#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <functional>
#include <mutex>
#include <CoLib/System/Export.hpp>

namespace co
{

    template <typename T = void>
    class Job;

    /////////////////////////////////////////////

    template <>
    class COLIB_SYSTEM_API Job<void>
    {

    public:
        enum State
        {
            Empty,
            Ready,
            Running,
            Done,
            Canceled,
            Error
        };

        State getState() const;

        void run();
        void wait() const;
        void cancel();

        Job(const Job &other) = delete;

        Job(const std::function<void()> &job = nullptr);
        ~Job();

    private:
        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        mutable State m_state;

        std::function<void()> m_job;
    };

    /////////////////////////////////////////////////////////////////////

    template <typename T>
    class COLIB_SYSTEM_API Job
    {

    public:
        const T &getResult() const;

        Job(const std::function<T()> &job = nullptr);
        ~Job() = default;

    private:
        T m_result;
    };

}

#include <CoLib/System/Job.inl>

#endif // COLIB_JOB_HPP