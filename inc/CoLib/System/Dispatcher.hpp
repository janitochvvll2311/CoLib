#ifndef COLIB_DISPATCHER_HPP
#define COLIB_DISPATCHER_HPP

#include <memory>
#include <list>
#include <mutex>
#include <functional>
#include <CoLib/System/Export.hpp>

namespace co
{

    using SharedJob = std::shared_ptr<std::function<void()>>;

    //////////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Dispatcher
    {

    public:
        bool attach(const SharedJob &job);
        bool detach(const SharedJob &job);

        SharedJob take();
        void wait() const;
        void run();

        Dispatcher(const Dispatcher &other) = delete;

        Dispatcher();
        ~Dispatcher();

    private:
        mutable std::mutex m_mutex;
        mutable std::mutex m_waiter;

        std::list<SharedJob> m_jobs;
    };

    //////////////////////////////////////////////////////////////////////////////

    using SharedDispatcher = std::shared_ptr<Dispatcher>;
    using WeakDispatcher = std::weak_ptr<Dispatcher>;

    void COLIB_SYSTEM_API runWorker(const WeakDispatcher& dispatcher);

    //////////////////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const extern COLIB_SYSTEM_API SharedDispatcher Main;
    }

}

#endif // COLIB_DISPATCHER_HPP