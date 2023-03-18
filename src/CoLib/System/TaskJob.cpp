#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/TaskJob.hpp>

namespace co
{

    Dispatcher *TaskJob::getDispatcher() const
    {
        return m_dispatcher;
    }

    BaseTask::State TaskJob::getState() const
    {
        return m_state;
    }

    const SharedTaskWork &TaskJob::getWork() const
    {
        return m_work;
    }

    /////////////////////////////////////////////////////////////////

    void TaskJob::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    void TaskJob::cancel()
    {
        m_monitor.lock();
        if (m_state != BaseTask::Running)
        {
            m_state = BaseTask::Canceled;
            m_waiter.unlock();
        }
        else
        {
            m_state = BaseTask::Canceled;
        }
        m_monitor.unlock();
    }

    TaskJob::TaskJob(const SharedTaskWork &work)
        : m_monitor(), m_waiter(), m_state(BaseTask::Empty), m_dispatcher(), m_work(work)
    {
        if (work != nullptr)
        {
            m_state = BaseTask::Ready;
            m_waiter.lock();
        }
    }

    TaskJob::~TaskJob()
    {
        cancel();
    }

    ////////////////////////////////////////////////////////////

    void TaskJob::onRun()
    {
        m_monitor.lock();
        if (m_state != BaseTask::Ready)
        {
            m_monitor.unlock();
            throw InvalidOperationException(ONLY_CAN_RUN_READY_TASKS_STRING);
        }
        m_state = BaseTask::Running;
        m_monitor.unlock();
        try
        {
            m_work->run();
            m_monitor.lock();
            if (m_state == BaseTask::Running)
            {
                m_state = BaseTask::Done;
                m_waiter.unlock();
            }
            m_monitor.unlock();
        }
        catch (...)
        {
            m_monitor.lock();
            if (m_state == BaseTask::Running)
            {
                m_state = BaseTask::Error;
                m_waiter.unlock();
            }
            m_monitor.unlock();
        }
    }

    void TaskJob::onAttach(Dispatcher *dispatcher)
    {
        m_dispatcher = dispatcher;
    }

    void TaskJob::onDetach()
    {
        m_dispatcher = nullptr;
    }

    ///////////////////////////////////////////////////////////////////////

    const s8t ONLY_CAN_RUN_READY_TASKS_STRING = "Only can run Ready Task instances";

}