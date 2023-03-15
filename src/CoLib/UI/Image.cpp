#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Image.hpp>

namespace co
{

    Image::Anchor Image::getHorizontalContentAnchor() const
    {
        return getHorizontalAnchor(m_image);
    }

    void Image::setHorizontalContentAnchor(Anchor value)
    {
        setHorizontalAnchor(m_image, value);
    }

    Image::Anchor Image::getVerticalContentAlignment() const
    {
        return getVerticalAnchor(m_image);
    }

    void Image::setVerticalContentAnchor(Anchor value)
    {
        setVerticalAnchor(m_image, value);
    }

    const SharedBackground &Image::getImage() const
    {
        return m_image;
    }

    Image::Image()
        : m_image(new Background())
    {
        attach(m_image);
    }

    Image::~Image() {}

    //////////////////////////////////////////////////////////////////

    void Image::onAttach(const SharedWidget &widget)
    {
        if (widget != m_image)
        {
            throw InvalidOperationException();
        }
        FrameLayout::onAttach(widget);
    }

    void Image::onDetach(const SharedWidget &widget)
    {
        throw InvalidOperationException();
    }

}