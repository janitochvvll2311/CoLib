#ifndef COLIB_DISPATCHER_HPP
#define COLIB_DISPATCHER_HPP

#include <memory>
#include <mutex>
#include <list>
#include <functional>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    class Dispatcher;
    using SharedDispatcher = std::shared_ptr<Dispatcher>;
    using WeakDispatcher = std::weak_ptr<Dispatcher>;

    using ExceptionHandler = std::function<void(const Exception &)>;

    //////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Dispatcher
    {
    public:
        void append(const SharedJob &job);
        void remove(const SharedJob &job);
        bool tryRemove(const SharedJob &job);

        SharedJob take();
        SharedJob wait();

        Dispatcher();
        ~Dispatcher();

        static const SharedDispatcher Main;

    private:
        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;
        std::list<SharedJob> m_jobs;
    };

    //////////////////////////////////////////////////////////////////////////////

    void COLIB_SYSTEM_API runWorker(
        const WeakDispatcher &dispatcher = Dispatcher::Main,
        const ExceptionHandler &handler = [](auto &exception) {});

}

#endif // COLIB_DISPATCHER_HPP