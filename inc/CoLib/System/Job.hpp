#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <functional>
#include <mutex>
#include <CoLib/Config.hpp>

namespace co
{

    class COLIB_SYSTEM_API Job
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

        Job(const std::function<void()> &job);
        ~Job();

    private:
        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        mutable State m_state;

        std::function<void()> m_job;
    };

}

#endif // COLIB_JOB_HPP