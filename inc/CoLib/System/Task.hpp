#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <memory>
#include <functional>
#include <CoLib/Config.hpp>

namespace co
{

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    template <typename T>
    class Task;

    template <typename T>
    using TaskWork = std::function<T()>;

    ////////////////////////////////////////

    class BaseTask
    {
    public:
        BaseTask();
        virtual ~BaseTask();

    protected:
        struct Work
        {
            virtual void run() = 0;
        };

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