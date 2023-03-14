#include <CoLib/System/Exception.hpp>
#include <CoLib/UI/Background.hpp>
#include <CoLib/UI/Image.hpp>

namespace co
{

    Image::Alignment Image::getHorizontalContentAlignment() const
    {
        return getHorizontalAlignment(m_image);
    }

    void Image::setHorizontalContentAlignment(Alignment value)
    {
        setHorizontalAlignment(m_image, value);
    }

    Image::Alignment Image::getVerticalContentAlignment() const
    {
        return getVerticalAlignment(m_image);
    }

    void Image::setVerticalContentAlignment(Alignment value)
    {
        setVerticalAlignment(m_image, value);
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