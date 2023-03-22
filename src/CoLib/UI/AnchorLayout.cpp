#define COLIB_UI_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Constants.hpp>
#include <CoLib/UI/AnchorLayout.hpp>

namespace co
{

    AnchorLayout::Anchor AnchorLayout::getHorizontalAnchor(const SharedNode &child) const
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return std::dynamic_pointer_cast<AnchorHolder>(holder)->hAnchor;
    }

    void AnchorLayout::setHorizontalAnchor(const SharedNode &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        std::dynamic_pointer_cast<AnchorHolder>(holder)->hAnchor = value;
    }

    AnchorLayout::Anchor AnchorLayout::getVerticalAnchor(const SharedNode &child) const
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return std::dynamic_pointer_cast<AnchorHolder>(holder)->vAnchor;
    }

    void AnchorLayout::setVerticalAnchor(const SharedNode &child, Anchor value)
    {
        auto holder = getHolder(child);
        if (holder == nullptr)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        std::dynamic_pointer_cast<AnchorHolder>(holder)->vAnchor = value;
    }

    AnchorLayout::AnchorLayout() {}
    AnchorLayout::~AnchorLayout() {}

    ///////////////////////////////////////////////////////////

    sf::Vector2f AnchorLayout::compactContent() const
    {
        sf::Vector2f cSize(0, 0);
        for (szt i = 0; i < getChildCount(); i++)
        {
            auto child = getChild(i);
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(child);
            if (inflatable)
            {
                auto size = inflatable->compact();
                cSize.x = std::max(cSize.x, size.x);
                cSize.y = std::max(cSize.y, size.y);
            }
        }
        return cSize;
    }

    void AnchorLayout::inflateContent() const
    {
        if (getChildCount() > 0)
        {
            sf::Vector2f innerSize = getInnerSize();
            for (auto &holder : getHolders())
            {
                auto _holder = std::dynamic_pointer_cast<AnchorHolder>(holder);
                auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                if (inflatable)
                {
                    auto size = inflatable->inflate(innerSize);
                    sf::Vector2f position(0, 0);
                    switch (_holder->hAnchor)
                    {
                    case Start:
                        break;
                    case End:
                        position.x = innerSize.x - size.x;
                        break;
                    case Center:
                        position.x = (innerSize.x - size.x) / 2;
                        break;
                    }
                    switch (_holder->vAnchor)
                    {
                    case Start:
                        break;
                    case End:
                        position.y = innerSize.y - size.y;
                        break;
                    case Center:
                        position.y = (innerSize.y - size.y) / 2;
                        break;
                    }
                    inflatable->place(position);
                }
            }
        }
    }

    AnchorLayout::SharedHolder AnchorLayout::createHolder() const
    {
        return std::make_shared<AnchorHolder>();
    }

}