#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <CoLib/System/Optional.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    class COLIB_SYSTEM_API TaskImpl
    {

    public:
        void start(const SharedDispatcher &dispatcher = co::dispatchers::Main);
        void wait() const;
        void cancel();

        ~TaskImpl();

    protected:
        TaskImpl(const SharedJob &job);

    private:
        SharedJob m_job;
    };

    /////////////////////////////////////////////////

    template <typename T>
    class Task : public TaskImpl
    {
    public:
        const Optional<T> &await() const;
        Task(const std::function<T()> &job = nullptr);
    };

    /////////////////////////////////////////////////

    template <>
    class Task<void> : public TaskImpl
    {
    public:
        Task(const std::function<void()> &job = nullptr);
    };

}

#include <CoLib/System/Task.inl>

#endif // COLIB_TASK_HPP