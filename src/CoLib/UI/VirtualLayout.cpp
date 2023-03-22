#define COLIB_UI_EXPORTS
#include <SFML/Window/Event.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/VirtualLayout.hpp>

namespace co
{

    const sf::Transform &VirtualLayout::getInnerTransform() const
    {
        return m_transform;
    }

    void VirtualLayout::setInnerTransform(const sf::Transform &value)
    {
        m_transform = value;
    }

    ///////////////////////////////////////////////////////////////////////////

    sf::Vector2f VirtualLayout::getInnerPoint(const sf::Vector2f &point) const
    {
        auto _point = FrameLayout::getInnerPoint(point);
        return m_transform.getInverse().transformPoint(_point);
    }

    VirtualLayout::VirtualLayout()
        : m_texture(), m_surface(), m_transform(sf::Transform::Identity)
    {
        co::Rectangle rectangle(1, 1);
        m_surface.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        setPoints(m_surface, rectangle);
    }

    VirtualLayout::~VirtualLayout() {}

    //////////////////////////////////////////////////////////////////////////////////////////////////

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        auto holder = getHolder();
        if (holder)
        {
            sf::Vector2f innerSize(getInnerSize());
            if (innerSize.x > 0 && innerSize.y > 0)
            {
                auto drawable = std::dynamic_pointer_cast<sf::Drawable>(holder->child);
                if (drawable)
                {
                    auto _states = states;
                    _states.transform = m_transform;
                    m_texture.clear(sf::Color::Transparent);
                    m_texture.draw(*drawable, _states);
                    m_texture.display();
                    //
                    auto &padding = getPadding();
                    _states = states;
                    _states.transform.translate({getLeft() + padding.left, getTop() + padding.top});
                    _states.texture = &(m_texture.getTexture());
                    target.draw(m_surface, _states);
                }
            }
        }
    }

    bool VirtualLayout::dispatchChildrenEvents(Node *target, const sf::Event &event) const
    {
        auto holder = getHolder();
        if (holder)
        {
            switch (event.type)
            {
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
                if (contains({f32t(event.mouseButton.x), f32t(event.mouseButton.y)}))
                {
                    auto innerPoint = getInnerPoint({f32t(event.mouseButton.x), f32t(event.mouseButton.y)});
                    auto _event = event;
                    _event.mouseButton.x = innerPoint.x;
                    _event.mouseButton.y = innerPoint.y;
                    return holder->child->dispatchEvent(target, _event);
                }
                break;
            default:
                return holder->child->dispatchEvent(target, event);
            }
        }
        return false;
    }

    sf::Vector2f VirtualLayout::compactContent() const
    {
        auto holder = getHolder();
        if (holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(holder->child);
            if (inflatable)
            {
                inflatable->compact();
            }
        }
        return {0, 0};
    }

    void VirtualLayout::updateContent() const
    {
        auto holder = getHolder();
        if (holder)
        {
            sf::Vector2f innerSize(getInnerSize());
            if (innerSize.x > 0 && innerSize.y > 0)
            {
                auto _ = m_texture.create(innerSize.x, innerSize.y);
                sf::Vector2f tSize(m_texture.getSize());
                setTexCoords(m_surface, {{0, 0}, tSize});
                fitPoints(m_surface, {{0, 0}, innerSize});
            }
        }
    }

}