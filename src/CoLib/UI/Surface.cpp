#define COLIB_UI_EXPORTS
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/Graphics/Rectangle.hpp>
#include <CoLib/Graphics/Utils.hpp>
#include <CoLib/UI/Surface.hpp>

namespace co
{

    Node *Surface::getParent() const
    {
        return m_parent;
    }

    const sf::Color &Surface::getColor() const
    {
        return m_color;
    }

    void Surface::setColor(const sf::Color &value)
    {
        m_color = value;
    }

    const SharedTexture &Surface::getTexture() const
    {
        return m_texture;
    }

    void Surface::setTexture(const SharedTexture &value)
    {
        m_texture = value;
    }

    sf::Vector2f Surface::compact()
    {
        setWidth(0);
        setHeight(0);
        return {0, 0};
    }

    sf::Vector2f Surface::inflate(const sf::Vector2f &size)
    {
        setWidth(size.x);
        setHeight(size.y);
        return size;
    }

    void Surface::place(const sf::Vector2f &position)
    {
        setLeft(position.x);
        setTop(position.y);
    }

    bool Surface::isValid() const
    {
        return m_isValid;
    }

    void Surface::invalidate()
    {
        m_isValid = false;
        auto parent = getParent();
        while (parent)
        {
            auto updatable = dynamic_cast<Updatable *>(parent);
            if (updatable)
            {
                updatable->invalidate();
                break;
            }
            parent = parent->getParent();
        }
    }

    Surface::Surface()
        : m_isValid(false), m_array(sf::PrimitiveType::TriangleFan),
          m_color(sf::Color::White), m_texture(nullptr),
          m_parent(nullptr)
    {
        Rectangle rectangle(1, 1);
        setPoints(m_array, rectangle);
        setColors(m_array, m_color);
    }

    Surface::~Surface() {}

    //////////////////////////////////////////////////////////////////////////////

    void Surface::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        update(false);
        if (getWidth() > 0 && getHeight() > 0)
        {
            if (m_texture != nullptr)
            {
                auto _states = states;
                _states.texture = m_texture.get();
                target.draw(m_array, _states);
            }
            else
            {
                target.draw(m_array, states);
            }
        }
    }

    void Surface::onAttach(Node *node)
    {
        m_parent = node;
    }

    void Surface::onDetach()
    {
        m_parent = nullptr;
    }

    void Surface::onUpdate() const
    {
        auto width = getWidth();
        auto height = getHeight();
        if (width > 0 && height > 0)
        {
            fitPoints(m_array, sf::FloatRect({getLeft(), getTop()}, {width, height}));
            setColors(m_array, m_color);
            if (m_texture != nullptr)
            {
                sf::Vector2f tSize(m_texture->getSize());
                setTexCoords(m_array, {{0, 0}, tSize});
            }
        }
        m_isValid = true;
    }

}