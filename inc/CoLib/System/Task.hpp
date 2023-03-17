#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <memory>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Optional.hpp>

namespace co
{

    template <typename T>
    class Task;

    ////////////////////////////////////////

    template <>
    class Task<void>
    {

    public:
        void start(const SharedDispatcher &dispatcher = Dispatcher::Main);
        void wait() const;
        void cancel();

        Task(const std::function<void()> &task);
        ~Task();

    private:
        class Job : public co::Job
        {

        public:
            Job(const std::function<void()> &job);
            virtual ~Job();

        protected:
            void onRun() override;

        private:
            std::function<void()> m_job;
        };

        std::shared_ptr<Job> m_job;
    };

    ///////////////////////////////////////////////////////////////////////////////

    template <typename T>
    class Task
    {
    public:
        const Optional<T> &getResult() const;

        void start(const SharedDispatcher &dispatcher = Dispatcher::Main);
        void wait() const;
        void cancel();

        Task(const std::function<T()> &task);
        ~Task();

    private:
        class Job : public co::Job
        {

        public:
            const Optional<T> &getResult() const;

            Job(const std::function<T()> &job);
            virtual ~Job();

        protected:
            void onRun() override;

        private:
            Optional<T> m_result;
            std::function<T()> m_job;
        };

        std::shared_ptr<Job> m_job;
    };

}

#include <CoLib/System/Task.inl>

#endif // COLIB_TASK_HPP