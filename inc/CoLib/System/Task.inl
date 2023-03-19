#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    inline Task<void>::Task(const TaskWork<void> &work)
        : BaseTask(std::make_shared<VoidWork>(work)) {}

    inline void Task<void>::VoidWork::run()
    {
        work();
    }

    inline Task<void>::VoidWork::VoidWork(const TaskWork<void> &_work)
        : work(_work) {}

    //////////////////////////////////////////////////////////////

    template <typename T>
    inline const std::optional<T> &Task<T>::await() const
    {
        wait();
        auto work = std::dynamic_pointer_cast<ResultWork>(getWork());
        if (!work)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        return work->result;
    }

    template <typename T>
    inline Task<T>::Task(const TaskWork<T> &work)
        : BaseTask(std::make_shared<ResultWork>(work)) {}

    template <typename T>
    inline void Task<T>::ResultWork::run()
    {
        result = work();
    }

    template <typename T>
    inline Task<T>::ResultWork::ResultWork(const TaskWork<T> &_work)
        : work(_work) {}

}