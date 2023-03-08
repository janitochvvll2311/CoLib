#include <iostream>
#include <CoLib/System/Constants.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/System/Notifier.hpp>

class Ax
{
public:
    co::Notifier<Ax, void()> notifer;
    void dispatch()
    {
        notifer.notify();
    }
};

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
    auto fx = std::make_shared<std::function<void()>>([]()
                                                      { std::cout << "Lambda 1 works\n"; });
    co::Notifier<void, void()> notifier;
    notifier.add(fx);
    notifier.notify();
    notifier.remove(fx);
    notifier.notify();

    Ax ax;
    auto afx = std::make_shared<std::function<void()>>([]()
                                                       { std::cout << "Lambda 2 works\n"; });
    ax.notifer.add(afx);
    ax.dispatch();
    ax.notifer.remove(afx);
    ax.dispatch();
    //
    std::cin.get();
    return 0;
}