#define COLIB_UI_EXPORTS
#include <CoLib/System/Exception.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    szt FrameLayout::getChildCount() const
    {
        if (m_holder)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }

    SharedNode FrameLayout::getChild(szt index) const
    {
        if (index == 0 && m_holder != nullptr)
        {
            return m_holder->child;
        }
        return nullptr;
    }

    FrameLayout::FrameLayout()
        : m_holder(nullptr) {}

    FrameLayout::~FrameLayout() {}

    //////////////////////////////////////////////////////////////////

    void FrameLayout::onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (m_holder)
        {
            auto drawable = std::dynamic_pointer_cast<sf::Drawable>(m_holder->child);
            if (drawable)
            {
                auto &padding = getPadding();
                auto _states = states;
                _states.transform.translate({getLeft() + padding.left, getTop() + padding.top});
                target.draw(*drawable, _states);
            }
        }
    }

    void FrameLayout::onAppend(const SharedNode &child)
    {
        if (m_holder != nullptr)
        {
            throw InvalidOperationException("Frame layout has a child already");
        }
        m_holder.reset(new Holder());
        m_holder->child = child;
        m_holder->hAnchor = Start;
        m_holder->vAnchor = Start;
    }

    void FrameLayout::onRemove(const SharedNode &child)
    {
        if (m_holder == nullptr || m_holder->child != child)
        {
            throw InvalidOperationException("Frame layout has another child already");
        }
        m_holder.reset();
    }

    sf::Vector2f FrameLayout::compactContent() const
    {
        if (m_holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_holder->child);
            if (inflatable)
            {
                return inflatable->compact();
            }
        }
        return {0, 0};
    }

    void FrameLayout::inflateContent() const
    {
        if (m_holder)
        {
            auto inflatable = std::dynamic_pointer_cast<Inflatable>(m_holder->child);
            if (inflatable)
            {
                auto &padding = getPadding();
                inflatable->inflate({getWidth() - padding.getHorizontal(), getHeight() - padding.getVertical()});
            }
        }
    }

}