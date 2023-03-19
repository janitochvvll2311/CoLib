#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    template <typename T>
    class Task;

    template <typename T>
    using TaskWork = std::function<T()>;

    ////////////////////////////////////////

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
        SharedJob m_job;
    };

    ////////////////////////////////////////

    template <>
    class Task<void>
        : public BaseTask
    {
    public:
        Task(const TaskWork<void> &work);
        ~Task();
    };

    ///////////////////////////////////////

    template <typename T>
    class Task
        : public BaseTask
    {
    public:
        Task(const TaskWork<T> &work);
        ~Task();
    };

}

#endif // COLIB_TASK_HPP