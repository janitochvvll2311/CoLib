#include <iostream>
#include <CoLib/System/Task.hpp>

void test()
{
    co::Task<void> voidTask;
    voidTask.wait();
    co::Task<int> intTask;
    intTask.wait();
}

int main()
{

    co::runCatching(
        test,
        [](const co::Exception &exception)
        {
            std::cout << exception.getReason() << '\n';
        });

    std::cin.get();
    return 0;
}