#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/TaskJob.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Task.hpp>

namespace co
{

    BaseTask::State BaseTask::getState() const
    {
        if (m_job != nullptr)
        {
            auto job = std::dynamic_pointer_cast<TaskJob>(m_job);
            return job->getState();
        }
        return Empty;
    }

    void BaseTask::start(const SharedDispatcher &dispatcher)
    {
        if (m_job == nullptr)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        dispatcher->append(m_job);
    }

    void BaseTask::wait() const
    {
        if (!m_job)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        auto dispatcher = m_job->getDispatcher();
        if (!dispatcher || dispatcher->remove(m_job))
        {
            m_job->run();
        }
    }

    void BaseTask::cancel()
    {
        if (m_job == nullptr)
        {
            throw InvalidOperationException(EMPTY_TASK_STRING);
        }
        auto job = std::dynamic_pointer_cast<TaskJob>(m_job);
        job->cancel();
    }

    BaseTask::BaseTask(const SharedWork &work)
        : m_job()
    {
        if (work != nullptr)
        {
            m_job.reset(new TaskJob(work));
        }
    }

    BaseTask::~BaseTask() {}

    /////////////////////////////////////////////////////

    const BaseTask::SharedWork &BaseTask::getWork() const
    {
        auto job = std::dynamic_pointer_cast<TaskJob>(m_job);
        return job->getWork();
    }

}