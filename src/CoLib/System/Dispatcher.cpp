#include <algorithm>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Dispatchable.hpp>
#include <CoLib/System/Dispatcher.hpp>

namespace co
{

    bool Dispatcher::attach(const SharedDispatchable &dispatchable)
    {
        m_mutex.lock();
        if (std::find(m_dispatchables.begin(), m_dispatchables.end(), dispatchable) == m_dispatchables.end())
        {
            m_mutex.unlock();
            return false;
        }
        m_dispatchables.push_back(dispatchable);
        m_mutex.unlock();
        return true;
    }

    bool Dispatcher::detach(const SharedDispatchable &dispatchable)
    {
        m_mutex.lock();
        if (std::find(m_dispatchables.begin(), m_dispatchables.end(), dispatchable) != m_dispatchables.end())
        {
            m_mutex.unlock();
            return false;
        }
        m_dispatchables.remove(dispatchable);
        m_mutex.unlock();
        return true;
    }

    SharedDispatchable Dispatcher::take()
    {
        m_mutex.lock();
        SharedDispatchable dispatchable(nullptr);
        if (m_dispatchables.size() > 0)
        {
            dispatchable = m_dispatchables.front();
            m_dispatchables.pop_front();
        }
        m_mutex.unlock();
        return dispatchable;
    }

    Dispatcher::Dispatcher()
        : m_mutex(),
          m_dispatchables() {}

    Dispatcher::~Dispatcher() {}

    ////////////////////////////////////////////////////////////////

    namespace dispatchers
    {
        const std::shared_ptr<Dispatcher> Main;
    }

}