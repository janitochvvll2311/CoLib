#ifndef COLIB_JOB_HPP
#define COLIB_JOB_HPP

#include <memory>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Dispatcher;
    using SharedDispatcher = std::shared_ptr<Dispatcher>;

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    /////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Job
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

        virtual State getState() const = 0;
        virtual SharedDispatcher getDispatcher() const = 0;

        virtual void run() = 0;
        virtual void wait() const = 0;
        virtual void cancel() const = 0;

        Job();
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
        virtual void onAttach(const SharedDispatcher &dispatcher) = 0;
        virtual void onDetach() = 0;

    private:
        void attach(const SharedDispatcher &dispatcher);
        void detach();
    };

}

#endif // COLIB_JOB_HPP