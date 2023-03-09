#ifndef COLIB_TASK_HPP
#define COLIB_TASK_HPP

#include <CoLib/System/Export.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Job.hpp>

namespace co
{

    template <typename T>
    using SharedJob = std::shared_ptr<Job<T>>;

    //////////////////////////////////

    template <typename T>
    class Task;

    ///////////////////////////////

    template <>
    class COLIB_SYSTEM_API Task<void>
    {

    public:
        void start(const SharedDispatcher &dispatcher = co::dispatchers::Main);
        void wait() const;
        void cancel();

        Task(const std::function<void()> &job);
        ~Task() = default;

    private:
        SharedJob<void> m_job;
    };

    ///////////////////////////////

    template <typename T>
    class Task : public Task<void>
    {
    };

}

#include <CoLib/System/Task.inl>

#endif // COLIB_TASK_HPP