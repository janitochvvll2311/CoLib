#define COLIB_UI_EXPORTS
#include <algorithm>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Constants.hpp>
#include <CoLib/UI/LinearLayout.hpp>

namespace co
{

    LinearLayout::Anchor LinearLayout::getAnchor(const SharedNode &widget) const
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return std::dynamic_pointer_cast<LinearHolder>(holder)->anchor;
    }

    void LinearLayout::setAnchor(const SharedNode &widget, Anchor value)
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        std::dynamic_pointer_cast<LinearHolder>(holder)->anchor = value;
    }

    f32t LinearLayout::getWeight(const SharedNode &widget) const
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        return std::dynamic_pointer_cast<LinearHolder>(holder)->weight;
    }

    void LinearLayout::setWeight(const SharedNode &widget, f32t value)
    {
        auto holder = getHolder(widget);
        if (!holder)
        {
            throw InvalidOperationException(NOT_CHILD_NODE_STTRING);
        }
        std::dynamic_pointer_cast<LinearHolder>(holder)->weight = value;
    }

    LinearLayout::Orientation LinearLayout::getOrientation() const
    {
        return m_orientation;
    }

    void LinearLayout::setOrientation(Orientation value)
    {
        m_orientation = value;
    }

    bool LinearLayout::isReverse() const
    {
        return m_isReverse;
    }

    void LinearLayout::setReverse(bool value)
    {
        m_isReverse = value;
    }

    LinearLayout::Anchor LinearLayout::getContentAnchor() const
    {
        return m_cAnchor;
    }

    void LinearLayout::setContentAnchor(Anchor value)
    {
        m_cAnchor = value;
    }

    LinearLayout::LinearLayout()
        : m_orientation(Horizontal), m_isReverse(false), m_cAnchor(Start) {}

    LinearLayout::~LinearLayout() {}

    //////////////////////////////////////////////////////////////////////

    sf::Vector2f LinearLayout::compactContent() const
    {
        sf::Vector2f cSize(0, 0);
        if (getChildCount() > 0)
        {
            auto &holders = getHolders();
            switch (m_orientation)
            {
            case Horizontal:
                for (auto &holder : holders)
                {
                    auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                    if (inflatable)
                    {
                        auto size = inflatable->compact();
                        cSize.x += size.x;
                        cSize.y = std::max(cSize.y, size.y);
                    }
                }
                break;
            case Vertical:
                for (auto &holder : holders)
                {
                    auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                    if (inflatable)
                    {
                        auto size = inflatable->compact();
                        cSize.y += size.y;
                        cSize.x = std::max(cSize.x, size.x);
                    }
                }
                break;
            }
        }
        return cSize;
    }

    void LinearLayout::inflateContent() const
    {
        if (getChildCount() > 0)
        {
            auto innerSize = getInnerSize();
            auto &holders = getHolders();
            m_length = 0;
            switch (m_orientation)
            {
            case Horizontal:
            {
                for (auto &holder : holders)
                {
                    auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                    if (inflatable)
                    {
                        auto _holder = std::dynamic_pointer_cast<LinearHolder>(holder);
                        auto size = inflatable->inflate({innerSize.x * _holder->weight, innerSize.y});
                        m_length += size.x;
                        _holder->size = size;
                    }
                }
            }
            break;
            case Vertical:
            {
                for (auto &holder : holders)
                {
                    auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                    if (inflatable)
                    {
                        auto _holder = std::dynamic_pointer_cast<LinearHolder>(holder);
                        auto size = inflatable->inflate({innerSize.x, innerSize.y * _holder->weight});
                        m_length += size.y;
                        _holder->size = size;
                    }
                }
            }
            break;
            }
        }
    }

    void LinearLayout::placeContent(const sf::Vector2f &origin) const
    {
        if (getChildCount() > 0)
        {
            auto innerSize = getInnerSize();
            f32t offset = 0;
            auto fixOffset = [&]()
            {
                if (offset > 0)
                {
                    switch (m_cAnchor)
                    {
                    case Start:
                        offset = 0;
                        break;
                    case End:
                        break;
                    case Center:
                        offset /= 2;
                    }
                }
                else
                {
                    offset = 0;
                }
            };
            auto aligHorizontal = [&](SharedHolder holder)
            {
                auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                if (inflatable)
                {
                    auto _holder = std::dynamic_pointer_cast<LinearHolder>(holder);
                    auto &size = _holder->size;
                    sf::Vector2f position(origin);
                    position.x += offset;
                    switch (_holder->anchor)
                    {
                    case Start:
                        break;
                    case End:
                        position.y += innerSize.y - size.y;
                        break;
                    case Center:
                        position.y += (innerSize.y - size.y) / 2;
                        break;
                    }
                    inflatable->place(position);
                    offset += size.x;
                }
            };
            auto alignVertical = [&](SharedHolder holder)
            {
                auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                if (inflatable)
                {
                    auto _holder = std::dynamic_pointer_cast<LinearHolder>(holder);
                    auto &size = _holder->size;
                    sf::Vector2f position(origin);
                    position.y += offset;
                    switch (_holder->anchor)
                    {
                    case Start:
                        break;
                    case End:
                        position.x += innerSize.x - size.x;
                        break;
                    case Center:
                        position.x += (innerSize.x - size.x) / 2;
                        break;
                    }
                    inflatable->place(position);
                    offset += size.y;
                }
            };
            auto &holders = getHolders();
            switch (m_orientation)
            {
            case Horizontal:
            {
                offset = innerSize.x - m_length;
                fixOffset();
                if (m_isReverse)
                {
                    for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                    {
                        aligHorizontal(*iterator);
                    }
                }
                else
                {
                    for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                    {
                        aligHorizontal(*iterator);
                    }
                }
            }
            break;
            case Vertical:
            {
                for (auto &holder : holders)
                {
                    auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
                    if (inflatable)
                    {
                        auto _holder = std::dynamic_pointer_cast<LinearHolder>(holder);
                        auto size = inflatable->inflate({innerSize.x, innerSize.y * _holder->weight});
                        m_length += size.y;
                        _holder->size = size;
                    }
                }
                offset = innerSize.y - m_length;
                fixOffset();
                if (m_isReverse)
                {
                    for (auto iterator = holders.rbegin(); iterator != holders.rend(); iterator++)
                    {
                        alignVertical(*iterator);
                    }
                }
                else
                {
                    for (auto iterator = holders.begin(); iterator != holders.end(); iterator++)
                    {
                        alignVertical(*iterator);
                    }
                }
            }
            break;
            }
        }
    }

    LinearLayout::SharedHolder LinearLayout::createHolder() const
    {
        return std::make_shared<LinearHolder>();
    }
}