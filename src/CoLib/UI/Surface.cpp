#define COLIB_UI_EXPORTS
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
        update();
        return size;
    }

    void Surface::place(const sf::Vector2f &position)
    {
        setLeft(position.x);
        setTop(position.y);
    }

    Surface::Surface()
        : m_array(sf::PrimitiveType::TriangleFan), m_color(sf::Color::White), m_parent(nullptr)
    {
        Rectangle rectangle(1, 1);
        setPoints(m_array, rectangle);
        setColors(m_array, m_color);
    }

    Surface::~Surface() {}

    //////////////////////////////////////////////////////////////////////////////

    void Surface::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        if (getWidth() > 0 && getHeight() > 0)
        {
            auto _states = states;
            _states.transform.translate({getLeft(), getTop()});
            target.draw(m_array, _states);
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

    //////////////////////////////////////////////////////////////////////////////

    void Surface::update() const
    {
        auto width = getWidth();
        auto height = getHeight();
        if (width > 0 && height > 0)
        {
            fitPoints(m_array, sf::FloatRect({0, 0}, {width, height}));
            setColors(m_array, m_color);
        }
    }

}