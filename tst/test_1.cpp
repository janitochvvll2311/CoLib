#include <iostream>
#include <thread>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>
#include <CoLib/System/Constants.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Notifier.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Task.hpp>

class Ax
{
public:
    co::Notifier<Ax, void()> notifer;
    void dispatch()
    {
        notifer.notify();
    }
};

auto makeTask(co::Task<void> *_task = nullptr)
{
    co::Task<void> task(
        [=]()
        {
            if (_task)
            {
                _task->wait();
            }
            sf::sleep(sf::seconds(2));
            auto hasher = std::hash<std::thread::id>();
            std::this_thread::get_id();
            std::cout << "Task Works: Thread " << hasher(std::this_thread::get_id()) << "\n";
            sf::sleep(sf::seconds(2));
        });
    return task;
}

int main()
{
    std::cout << co::LIBRARY_VERSION << "\n";
    try
    {
        throw co::NotImplementedException("Code no implemented yet");
    }
    catch (const std::exception &exception)
    {
        std::cout << exception.what() << "\n";
    }
    //
    auto fx = std::make_shared<std::function<void()>>(
        []()
        {
            std::cout << "Lambda 1 works\n";
        });
    co::Notifier<void, void()> notifier;
    notifier.add(fx);
    notifier.notify();
    notifier.remove(fx);
    notifier.notify();

    Ax ax;
    auto afx = std::make_shared<std::function<void()>>(
        []()
        {
            std::cout << "Lambda 2 works\n";
        });
    ax.notifer.add(afx);
    ax.dispatch();
    ax.notifer.remove(afx);
    ax.dispatch();
    //
    std::thread worker1(co::runWorker, co::dispatchers::Main);
    //
    auto t1 = makeTask();
    auto t2 = makeTask();
    auto t3 = makeTask(&t1);
    auto t4 = makeTask(&t2);

    t4.start();
    t3.start();
    t2.start();
    t1.start();

    t2.cancel();
    std::cout << "END\n";
    //
    std::cin.get();
    return 0;
}