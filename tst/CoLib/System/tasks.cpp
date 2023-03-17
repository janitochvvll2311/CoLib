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
            std::hash<std::thread::id> hasher;
            std::cout << hasher(std::this_thread::get_id());
            std::cout << ": Running\n";
            sf::sleep(sf::seconds(2));
            std::cout << hasher(std::this_thread::get_id());
            std::cout << ": Done\n";
        });
    return task;
}

auto makeTask(int result)
{
    co::Task<int> task(
        [=]()
        {
            std::hash<std::thread::id> hasher;
            std::cout << hasher(std::this_thread::get_id());
            std::cout << ": Running\n";
            sf::sleep(sf::seconds(2));
            std::cout << hasher(std::this_thread::get_id());
            std::cout << ": Done\n";
            return result;
        });
    return task;
}

auto runWorker()
{
    std::thread worker([]()
                       { co::runWorker(co::Dispatcher::Main); });
    worker.detach();
}

void test()
{
    runWorker();
    runWorker();
    runWorker();
    runWorker();
    runWorker();
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