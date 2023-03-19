#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/TaskImpl.hpp>

namespace co
{

    Dispatcher *TaskImpl::getDispatcher() const
    {
        return m_dispatcher;
    }

    BaseTask::State TaskImpl::getState() const
    {
        return m_state;
    }

    const SharedTaskWork &TaskImpl::getWork() const
    {
        return m_work;
    }

    /////////////////////////////////////////////////////////////////

    void TaskImpl::wait() const
    {
        m_waiter.lock();
        m_waiter.unlock();
    }

    void TaskImpl::cancel()
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

    TaskImpl::TaskImpl(const SharedTaskWork &work)
        : m_monitor(), m_waiter(), m_state(BaseTask::Empty), m_dispatcher(), m_work(work)
    {
        if (work != nullptr)
        {
            m_state = BaseTask::Ready;
            m_waiter.lock();
        }
    }

    TaskImpl::~TaskImpl()
    {
        cancel();
    }

    ////////////////////////////////////////////////////////////

    void TaskImpl::onRun()
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

    void TaskImpl::onAttach(Dispatcher *dispatcher)
    {
        m_dispatcher = dispatcher;
    }

    void TaskImpl::onDetach()
    {
        m_dispatcher = nullptr;
    }

    ///////////////////////////////////////////////////////////////////////

    const s8t ONLY_CAN_RUN_READY_TASKS_STRING = "Only can run Ready Task instances";

}