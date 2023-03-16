#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Utils.hpp>

namespace co
{

    void COLIB_SYSTEM_API runCatching(const std::function<void()> &callable, const std::function<void(const Exception &)> &handler)
    {
        try
        {
            callable();
        }
        catch (const Exception &exception)
        {
            handler(exception);
        }
        catch (...)
        {
            handler(Exception(UNKNOWN_EXCEPTION_MESSAGE));
        }
    }

}