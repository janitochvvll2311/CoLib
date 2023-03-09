#include <CoLib/System/Task.hpp>

namespace co {
    
    void Task<void>::start(const SharedDispatcher& dispatcher) {
        dispatcher->attach([](){

        });
    }

}