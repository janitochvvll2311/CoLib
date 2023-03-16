#include <iostream>
#include <CoLib/System/Object.hpp>

class Ax : public co::Object
{

public:
    void test()
    {
        auto self = cast<Ax>();
        if (self)
        {
            std::cout << "Safe initialized\n";
        }
        else
        {
            std::cout << "Raw initialized\n";
        }
    }
};

int main()
{

    Ax ax1;
    ax1.test();

    auto ax2 = Ax::create<Ax>();
    ax2->test();

    return 0;
}