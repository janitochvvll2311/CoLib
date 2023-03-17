#include <iostream>
#include <thread>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Utils.hpp>
#include <CoLib/System/Task.hpp>

auto makeTask()
{
    co::Task<void> task(
        []()
        {
            std::cout << "Running\n";
            sf::sleep(sf::seconds(2));
            std::cout << "Done\n";
        });
    return task;
}

auto makeTask(int result)
{
    co::Task<int> task(
        [=]()
        {
            std::cout << "Running\n";
            sf::sleep(sf::seconds(2));
            std::cout << "Done\n";
            return result;
        });
    return task;
}

void test()
{
    makeTask().start();
    makeTask(1).start();
    makeTask().start();
    makeTask(2).start();
    makeTask().start();
    makeTask(3).start();
    makeTask().start();
    makeTask(4).start();
    makeTask().start();
    makeTask(5).start();
    co::runWorker(co::Dispatcher::Main);
}

int main()
{

    co::runCatching(
        test,
        [](auto &exception)
        {
            std::cout << exception.getReason() << "\n";
        });

    std::cin.get();
    return 0;
}