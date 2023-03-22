#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/TaskImpl.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    BaseTask::State BaseTask::getState() const
    {
        if (m_impl != nullptr)
        {
            auto job = std::dynamic_pointer_cast<TaskImpl>(m_impl);
            return job->getState();
        }
        return Empty;
    }

    void BaseTask::start(const SharedDispatcher &dispatcher)
    {
        if (m_impl == nullptr)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        dispatcher->append(m_impl);
    }

    void BaseTask::wait() const
    {
        if (!m_impl)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        auto dispatcher = m_impl->getDispatcher();
        if (!dispatcher || dispatcher->tryRemove(m_impl))
        {
            m_impl->run();
        }
        else
        {
            auto job = std::dynamic_pointer_cast<TaskImpl>(m_impl);
            job->wait();
        }
    }

    void BaseTask::cancel()
    {
        if (m_impl == nullptr)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        auto job = std::dynamic_pointer_cast<TaskImpl>(m_impl);
        job->cancel();
    }

    BaseTask::BaseTask(const SharedWork &work)
        : m_impl()
    {
        if (work != nullptr)
        {
            m_impl.reset(new TaskImpl(work));
        }
    }

    BaseTask::~BaseTask() {}

    /////////////////////////////////////////////////////

    const BaseTask::SharedWork &BaseTask::getWork() const
    {
        auto job = std::dynamic_pointer_cast<TaskImpl>(m_impl);
        return job->getWork();
    }

}