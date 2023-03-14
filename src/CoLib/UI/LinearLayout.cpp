#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/LinearLayout.hpp>

namespace co
{

    bool LinearLayout::isValid() const
    {
        if (!Block::isValid())
        {
            return false;
        }
        for (auto &holder : m_holders)
        {
            if (!holder->getWidget()->isValid())
            {
                return false;
            }
        }
        return true;
    }

    void LinearLayout::invalidate()
    {
        Block::invalidate();
        for (auto &holder : m_holders)
        {
            holder->getWidget()->invalidate();
        }
    }

    void LinearLayout::compact()
    {
    }

    void LinearLayout::inflate(const sf::Vector2f &size)
    {
    }

    LinearLayout::LinearLayout()
        : m_holders() {}

    LinearLayout::~LinearLayout() {}

    //////////////////////////////////////////////////////////////////////

    void LinearLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        Block::onDraw(target, states);
        if (m_holders.size() > 0)
        {
            auto &padding = getPadding();
            auto _states = states;
            _states.transform.translate({padding.left, padding.top});
            for (auto &holder : m_holders)
            {
                target.draw(*holder->getWidget(), _states);
            }
        }
    }

    void LinearLayout::onUpdate() const
    {
        Block::onUpdate();
        for (auto &holder : m_holders)
        {
            holder->getWidget()->update(true);
        }
    }

    void LinearLayout::onAttach(const SharedWidget &widget)
    {
        auto holder = std::make_shared<LinearWidgetHolder>();
        holder->setWidget(widget);
        m_holders.push_back(holder);
    }

    void LinearLayout::onDetach(const SharedWidget &widget)
    {
        m_holders.remove_if([&](auto &holder)
                            { return holder->getWidget() == widget; });
    }

}