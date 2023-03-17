#include <iostream>
#include <thread>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <CoLib/System/Dispatcher.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Job.hpp>
#include <CoLib/System/Utils.hpp>

class Job : public co::Job
{

public:
    Job() : co::Job(Ready) {}
    ~Job() {}

protected:
    void onRun() override
    {
        std::cout << "Running\n";
        sf::sleep(sf::seconds(2));
        std::cout << "Done\n";
    }
};

void test()
{

    auto dispatcher = co::create<co::Dispatcher>();
    std::thread worker(
        [&]()
        {
            co::runWorker(dispatcher);
        });
    worker.detach();
    dispatcher->append(co::create<Job>());
    dispatcher->append(co::create<Job>());
    auto last = co::create<Job>();
    dispatcher->append(last);
    dispatcher->append(co::create<Job>());
    dispatcher->append(co::create<Job>());
    last->wait();
    dispatcher.reset();
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