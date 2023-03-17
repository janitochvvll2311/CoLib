#include <iostream>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Utils.hpp>

int main()
{

    co::runCatching(
        []()
        {
            auto dispatcher = co::Object::create<co::Dispatcher>();
        },
        [](auto &exception)
        {
            std::cout << exception.getReason() << "\n";
        });

    std::cin.get();
    return 0;
}