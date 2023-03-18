#ifndef COLIB_TASK_JOB_HPP
#define COLIB_TASK_JOB_HPP

#include <mutex>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    using SharedTaskWork = std::shared_ptr<BaseTask::Work>;

    /////////////////////////////////////////////////////////////////

    class TaskJob
        : public Job
    {

    public:
        Dispatcher *getDispatcher() const override;
        BaseTask::State getState() const;
        const SharedTaskWork &getWork() const;

        void wait() const;
        void cancel();

        TaskJob(const SharedTaskWork &work);
        virtual ~TaskJob();

    protected:
        void onRun() override;
        void onAttach(Dispatcher *dispatcher) override;
        void onDetach() override;

    private:
        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        mutable BaseTask::State m_state;
        Dispatcher *m_dispatcher;
        SharedTaskWork m_work;
    };

    /////////////////////////////////////////////////////////////////////////

    const extern s8t COLIB_SYSTEM_API ONLY_CAN_RUN_READY_TASKS_STRING;

}

#endif // COLIB_TASK_JOB_HPP