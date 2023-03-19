#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <optional>
#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    template <typename T>
    class Task;

    template <typename T>
    using TaskWork = std::function<T()>;

    class TaskImpl;
    using SharedTaskImpl = std::shared_ptr<TaskImpl>;

    ///////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API BaseTask
    {
    public:
        struct Work;
        using SharedWork = std::shared_ptr<Work>;

        struct Work
        {
            virtual void run() = 0;
        };

        enum State
        {
            Empty,
            Ready,
            Running,
            Done,
            Canceled,
            Error
        };

        /////////////////////////////////////////////////////

        State getState() const;

        void start(const SharedDispatcher &dispatcher = Dispatcher::Main);
        void wait() const;
        void cancel();

        BaseTask(const SharedWork &work = nullptr);
        virtual ~BaseTask();

    protected:
        const SharedWork &getWork() const;

    private:
        SharedTaskImpl m_impl;
    };

    ////////////////////////////////////////

    template <>
    class Task<void>
        : public BaseTask
    {
    public:
        Task(const TaskWork<void> &work = nullptr);
        ~Task() = default;

    private:
        struct VoidWork : public Work
        {
            void run() override;
            VoidWork(const TaskWork<void> &_work);
            TaskWork<void> work;
        };
    };

    ///////////////////////////////////////

    template <typename T>
    class Task
        : public BaseTask
    {
    public:
        const std::optional<T> &await() const;

        Task(const TaskWork<T> &work = nullptr);
        ~Task() = default;

    private:
        struct ResultWork : public Work
        {
            void run() override;
            ResultWork(const TaskWork<T> &_work);
            TaskWork<T> work;
            std::optional<T> result;
        };
    };

}

#include <CoLib/System/Task.inl>

#endif // COLIB_TASK_HPP