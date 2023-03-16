#include <iostream>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Utils.hpp>

int main()
{

    auto logger = [](const co::Exception &error)
    {
        std::cout << error.getReason() << '\n';
    };

    co::runCatching([]()
                    { throw co::Exception(); },
                    logger);
    co::runCatching([]()
                    { throw co::NotImplementedException(); },
                    logger);
    co::runCatching([]()
                    { throw co::InvalidOperationException(); },
                    logger);
    co::runCatching([]()
                    { throw co::InvalidValueException(); },
                    logger);
    co::runCatching([]()
                    { throw co::InvalidStateException(); },
                    logger);

    std::cin.get();
    return 0;
}