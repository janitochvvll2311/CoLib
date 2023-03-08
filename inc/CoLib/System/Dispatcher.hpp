#ifndef COLIB_DISPATCHER_HPP
#define COLIB_DISPATCHER_HPP

#include <memory>
#include <list>
#include <mutex>
#include <future>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Dispatchable;
    using SharedDispatchable = std::shared_ptr<Dispatchable>;

    //////////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Dispatcher
    {

    public:
        bool attach(const SharedDispatchable &dispatchable);
        bool detach(const SharedDispatchable &dispatchable);

        SharedDispatchable take();

        Dispatcher(const Dispatcher &other) = delete;

        Dispatcher();
        ~Dispatcher();

    private:
        mutable std::mutex m_mutex;
        std::list<SharedDispatchable> m_dispatchables;
    };

    //////////////////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const extern COLIB_SYSTEM_API std::shared_ptr<Dispatcher> Main;
    }

}

#endif // COLIB_DISPATCHER_HPP