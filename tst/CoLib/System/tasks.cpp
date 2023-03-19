#include <iostream>
#include <thread>
#include <string>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <CoLib/System/Task.hpp>

auto logger(const co::Exception &exception)
{
    std::cout << exception.getReason() << '\n';
}

auto runWorker()
{
    std::thread worker([]()
                       { co::runWorker(co::Dispatcher::Main, logger); });
    worker.detach();
}

auto makeTask()
{
    co::Task<void> task(
        []()
        {
            std::cout << "Begin ---\n";
            sf::sleep(sf::seconds(2));
            std::cout << "End\n";
        });
    return task;
}

auto makeTask(int value)
{
    co::Task<int> task(
        [=]()
        {
            std::cout << ("Begin " + std::to_string(value) + "\n");
            sf::sleep(sf::seconds(2));
            std::cout << ("End " + std::to_string(value) + "\n");
            return value;
        });
    return task;
}

void test()
{
    runWorker();
    runWorker();
    runWorker();
    auto task = makeTask(3);
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
    std::cout << ("Result is: " + std::to_string(task.await().value()) + "\n");
}

int main()
{

    co::runCatching(test, logger);

    std::cin.get();
    return 0;
}