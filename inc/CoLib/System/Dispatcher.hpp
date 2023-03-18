#ifndef COLIB_DISPATCHER_HPP
#define COLIB_DISPATCHER_HPP

#include <memory>
#include <CoLib/System/Export.hpp>

namespace co
{

    class Job;
    using SharedJob = std::shared_ptr<Job>;

    class Dispatcher;
    using SharedDispatcher = std::shared_ptr<Dispatcher>;

    //////////////////////////////////////////////////////////////

    class COLIB_SYSTEM_API Dispatcher
    {
    public:
        bool append(const SharedJob &job);
        bool remove(const SharedJob &job);

        static const SharedDispatcher Main;
    };

}

#endif // COLIB_DISPATCHER_HPP