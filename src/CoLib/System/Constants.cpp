#define COLIB_SYSTEM_EXPORTS
#include <CoLib/System/Constants.hpp>

namespace co
{

    const s8t LIBRARY_VERSION_STRING = COLIB_VERSION_STRING;
    const s8t UNKNOWN_EXCEPTION_STRING = "Unknown exception";
    const s8t NOT_IMPLEMENTED_EXCEPTION_STRING = "Not implemented exception";
    const s8t INVALID_OPERATION_EXCEPTION_STRING = "Invalid operation exception";

    const s8t JOB_STILL_ATTACHED_STRING = "This Job is still attached to a Dispatcher";
    const s8t JOB_ALREADY_ATTACHED_STRING = "This Job is already attached to a Dispatcher";
    const s8t JOB_ALREADY_DETACHED_STRING = "This Job is already detached from the Dispatcher";

    const s8t EMPTY_TASK_STRING = "The Task was Empty";

}