#include <iostream>
#include <thread>
#include <SFML/System/Time.hpp>
#include <SFML/System/Sleep.hpp>
#include <CoLib/System/Constants.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Notifier.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Job.hpp>

class Ax
{
public:
    co::Notifier<Ax, void()> notifer;
    void dispatch()
    {
        notifer.notify();
    }
};

auto makeJob()
{
    auto job = std::make_shared<std::function<void()>>(
        []()
        {
            sf::sleep(sf::seconds(2));
            auto hasher = std::hash<std::thread::id>();
            std::this_thread::get_id();
            std::cout << "It Works: Thread " << hasher(std::this_thread::get_id()) << "\n";
            sf::sleep(sf::seconds(2));
        });
    return job;
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
    worker1.detach();
    std::thread worker2(co::runWorker, co::dispatchers::Main);
    worker2.detach();
    std::thread worker3(co::runWorker, co::dispatchers::Main);
    worker3.detach();
    std::thread worker4(co::runWorker, co::dispatchers::Main);
    worker4.detach();
    //
    co::dispatchers::Main->attach(makeJob());
    co::dispatchers::Main->attach(makeJob());
    co::dispatchers::Main->attach(makeJob());
    co::dispatchers::Main->attach(makeJob());
    //
    auto job = std::make_shared<co::Job>(
        []()
        {
            sf::sleep(sf::seconds(2));
            auto hasher = std::hash<std::thread::id>();
            std::this_thread::get_id();
            std::cout << "Job Works: Thread " << hasher(std::this_thread::get_id()) << "\n";
            sf::sleep(sf::seconds(2));
        });
    co::dispatchers::Main->attach(std::make_shared<std::function<void()>>(
        [=]()
        {
            job->run();
        }));
    // job->cancel();
    job->wait();
    std::cout << "END\n";
    std::cin.get();
    return 0;
}