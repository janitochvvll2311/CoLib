#ifndef COLIB_DISPATCHER_HPP
#define COLIB_DISPATCHER_HPP

#include <list>
#include <mutex>
#include <functional>
#include <CoLib/System/Object.hpp>

namespace co
{

    class Exception;

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    class Dispatcher;
    using SharedDispatcher = std::shared_ptr<Dispatcher>;

    //////////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Dispatcher
        : public Object
    {

    public:
        void append(const SharedJob &job);
        void remove(const SharedJob &job);

        SharedJob take();
        void wait() const;
        void run();

        Dispatcher(const Dispatcher &other) = delete;

        Dispatcher();
        ~Dispatcher();

    private:
        SharedDispatcher getInstance();

        mutable std::mutex m_monitor;
        mutable std::mutex m_waiter;

        std::list<SharedJob> m_jobs;
    };

    //////////////////////////////////////////////////////////////////////////////

    using SharedDispatcher = std::shared_ptr<Dispatcher>;
    using WeakDispatcher = std::weak_ptr<Dispatcher>;

    void COLIB_SYSTEM_API runWorker(
        const WeakDispatcher &dispatcher,
        const std::function<void(const Exception &)> &handler = [](auto &exception) {});

    //////////////////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const extern COLIB_SYSTEM_API SharedDispatcher Main;
    }

}

#endif // COLIB_DISPATCHER_HPP