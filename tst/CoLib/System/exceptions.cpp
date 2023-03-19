#include <iostream>
#include <CoLib/System/Exception.hpp>

int main()
{

    auto logger = [](const co::Exception &exception)
    {
        std::cout << exception.getReason() << '\n';
    };

    co::runCatching(
        []()
        {
            throw co::Exception();
        },
        logger);
    co::runCatching(
        []()
        {
            throw co::NotImplementedException();
        },
        logger);
    co::runCatching(
        []()
        {
            try
            {
                throw co::InvalidOperationException();
            }
            catch (...)
            {
                std::cout << "Rethrow\n";
                throw;
            }
        },
        logger);

    std::cin.get();
    return 0;
}