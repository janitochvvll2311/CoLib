#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <functional>
#include <mutex>
#include <memory>
#include <CoLib/System/Export.hpp>
#include <CoLib/System/Optional.hpp>

namespace co
{

    class Dispatcher;

    /////////////////////////////////////////

    class COLIB_SYSTEM_API JobImpl
    {

        friend Dispatcher;

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

        Dispatcher *const getDispatcher() const;

        void run();
        void wait() const;
        void cancel();

        JobImpl(const JobImpl &other) = delete;
        ~JobImpl();

    protected:
        virtual void onRun() = 0;
        JobImpl(State state);

    private:
        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        mutable State m_state;

        Dispatcher *m_dispatcher;
    };

    /////////////////////////////////////////////////////////////////////

    template <typename T>
    class Job : public JobImpl
    {

    public:
        const Optional<T> &getResult() const;
        Job(const std::function<T()> &job = nullptr);

    private:
        void onRun() override;

        Optional<T> m_result;
        const std::function<T()> m_job;
    };

    /////////////////////////////////////////////////////////////////////

    template <>
    class Job<void> : public JobImpl
    {

    public:
        Job(const std::function<void()> &job = nullptr);

    private:
        void onRun() override;

        const std::function<void()> m_job;
    };

}

#include <CoLib/System/Job.inl>

#endif // COLIB_JOB_HPP