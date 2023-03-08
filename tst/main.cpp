#include <iostream>
#include <CoLib/System/Constants.hpp>
#include <CoLib/System/Exception.hpp>

int main()
{
    std::cout << co::LIBRARY_VERSION << "\n";
    try
    {
        throw co::Exception("Generic exception");
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what() << "\n";
    }
    std::cin.get();
    return 0;
}