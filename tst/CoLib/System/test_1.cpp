#include <iostream>
#include <CoLib/System/Object.hpp>

class Ax
{

public:
    void test()
    {

        auto *object = dynamic_cast<co::Object<Ax> *>(this);
        if (object)
        {
            auto self = object->getSelf();
            if (self)
            {
                auto x = 0;
            }
            auto x = 0;
        }
        auto x = 0;
    }

    Ax() {}
    virtual ~Ax() {}

    int a;
    int b;
};

int main()
{

    Ax obj1;
    obj1.test();

    auto obj2 = co::Object<Ax>::create();
    obj2->test();

    return 0;
}