#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/UI/VirtualLayout.hpp>

namespace co
{

    void VirtualLayout::compact()
    {
        FrameLayout::compact();
        Block::compact();
    }

    VirtualLayout::VirtualLayout()
        : m_texture(), m_surface()
    {
        co::Rectangle rectangle(1, 1);
        m_surface.setPrimitiveType(sf::PrimitiveType::TriangleFan);
        m_surface.setPoints(rectangle);
    }

    VirtualLayout::~VirtualLayout() {}

    //////////////////////////////////////////////////////////////////

    void VirtualLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        auto widget = getWidget();
        if (widget)
        {
            sf::Vector2f size(getInnerWidth(), getInnerHeight());
            if (size.x > 0 && size.y > 0)
            {
                m_texture.clear(sf::Color::Magenta);
                m_texture.draw(*widget);
                m_texture.display();
                auto &padding = getPadding();
                auto _states = states;
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