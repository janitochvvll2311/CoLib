#define COLIB_UI_EXPORTS
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <CoLib/UI/Surface.hpp>
#include <CoLib/UI/Image.hpp>

namespace co
{

    Node *Image::getParent() const
    {
        return m_root.getParent();
    }

    Image::Anchor Image::getHorizontalContentAnchor()
    {
        return m_root.getHorizontalAnchor(m_root.getChild(0));
    }

    void Image::setHorizontalContentAnchor(Anchor value)
    {
        m_root.setHorizontalAnchor(m_root.getChild(0), value);
    }

    Image::Anchor Image::getVerticalContentAnchor()
    {
        return m_root.getVerticalAnchor(m_root.getChild(0));
    }

    void Image::setVerticalContentAnchor(Anchor value)
    {
        m_root.setVerticalAnchor(m_root.getChild(0), value);
    }

    Block &Image::getBlock()
    {
        return m_root;
    }

    const Block &Image::getBlock() const
    {
        return m_root;
    }

    Surface &Image::getSurface()
    {
        return *(std::dynamic_pointer_cast<Surface>(m_root.getChild(0)));
    }

    const Surface &Image::getSurface() const
    {
        return *(std::dynamic_pointer_cast<Surface>(m_root.getChild(0)));
    }

    sf::Vector2f Image::compact()
    {
        return m_root.compact();
    }

    sf::Vector2f Image::inflate(const sf::Vector2f &size)
    {
        return m_root.inflate(size);
    }

    void Image::place(const sf::Vector2f &position)
    {
        m_root.place(position);
    }

    Image::Image()
        : m_root()
    {
        m_root.append(std::make_shared<Surface>());
    }

    Image::~Image() {}

    //////////////////////////////////////////////////////////

    void Image::draw(sf::RenderTarget &target, const sf::RenderStates &states) const
    {
        target.draw(m_root, states);
    }

    void Image::onAttach(Node *parent)
    {
        m_root.attach(parent);
    }

    void Image::onDetach()
    {
        m_root.detach();
    }

}