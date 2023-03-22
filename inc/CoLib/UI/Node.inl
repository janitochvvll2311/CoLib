#include <CoLib/UI/Node.hpp>

namespace co
{

    template <typename T>
    inline T *Node::closestInstance() const
    {
        auto parent = getParent();
        while (parent)
        {
            auto *instance = dynamic_cast<T *>(parent);
            if (instance)
            {
                return instance;
            }
            parent = parent->getParent();
        }
        return nullptr;
    }

}