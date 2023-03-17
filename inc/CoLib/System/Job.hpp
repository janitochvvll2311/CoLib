#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <mutex>
#include <CoLib/System/Object.hpp>

namespace co
{

    class Dispatcher;
    using SharedDispatcher = std::shared_ptr<Dispatcher>;
    using WeakDispatcher = std::weak_ptr<Dispatcher>;

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    /////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Job
        : public Object
    {

    public:
        enum State
        {
            Empty,
            Ready,
            Running,
            Done,
            Error,
            Canceled
        };

        State getState() const;
        SharedDispatcher getDispatcher() const;

        void run();
        void wait() const;
        void cancel();

        Job(State state = Empty);
        virtual ~Job();

        ////////////////////////////////////////

        class Manager final
        {

        public:
            void attach(const SharedDispatcher &dispatcher);
            void detach();

            Manager(const SharedJob &job);
            ~Manager();

        private:
            SharedJob m_job;
        };

    protected:
        virtual void onRun() = 0;

    private:
        void attach(const SharedDispatcher &dispatcher);
        void detach();

        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        State m_state;
        WeakDispatcher m_dispatcher;
    };

}

#endif // COLIB_JOB_HPP