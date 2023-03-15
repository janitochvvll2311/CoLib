#include <CoLib/Graphics/Rectangle.hpp>
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
        return m_transform.getInverse().transformPoint(point);
    }

    VirtualLayout::VirtualLayout()
        : m_texture(), m_surface(), m_transform(sf::Transform::Identity)
    {
        co::Rectangle rectangle(1, 1);
        m_surface.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        m_surface.setPoints(rectangle);
    }

    VirtualLayout::~VirtualLayout() {}

    //////////////////////////////////////////////////////////////////////////////////////////////////

    sf::Vector2f VirtualLayout::getContentSize() const
    {
        return {0, 0};
    }

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        auto widget = getWidget();
        if (widget)
        {
            sf::Vector2f size(getInnerWidth(), getInnerHeight());
            if (size.x > 0 && size.y > 0)
            {
                auto _states = states;
                _states.transform = m_transform;
                m_texture.clear(sf::Color::Transparent);
                m_texture.draw(*widget, _states);
                m_texture.display();
                //
                auto &padding = getPadding();
                _states = states;
                _states.transform.translate({padding.left, padding.top});
                target.draw(m_surface, _states);
            }
        }
    }

    void VirtualLayout::onUpdate() const
    {
        FrameLayout::onUpdate();
        if (getWidget())
        {
            sf::Vector2f size(getInnerWidth(), getInnerHeight());
            if (size.x > 0 && size.y > 0)
            {
                auto _ = m_texture.create(size.x, size.y);
                m_surface.setTexture(&(m_texture.getTexture()));
                m_surface.fitPoints({{0, 0}, size});
            }
        }
    }

}