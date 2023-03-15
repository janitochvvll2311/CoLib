#include <SFML/Window/Event.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/VirtualLayout.hpp>

namespace co
{

    const sf::Transform &VirtualLayout::getInnerTransform() const
    {
        return m_transform;
    }

    void VirtualLayout::setInnterTransform(const sf::Transform &value)
    {
        m_transform = value;
    }

    ///////////////////////////////////////////////////////////////////////////

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

    bool VirtualLayout::dispatchInnerEvent(const SharedWidget &widget, Widget *target, const sf::Event &event) const
    {
        switch (event.type)
        {
        case sf::Event::MouseButtonPressed:
        case sf::Event::MouseButtonReleased:
        {
            auto &margin = getMargin();
            auto &padding = getPadding();
            auto _event = event;
            sf::Vector2f point(event.mouseButton.x - (margin.getHorizontal() + padding.getHorizontal()),
                               event.mouseButton.y - (margin.getVertical() + padding.getVertical()));
            point = m_transform.getInverse().transformPoint(point);
            _event.mouseButton.x = point.x;
            _event.mouseButton.y = point.y;
            return widget->dispatchEvent(target, _event);
        }
        default:
            return widget->dispatchEvent(target, event);
        }
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