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
        append(m_image);
    }

    Image::~Image() {}

    //////////////////////////////////////////////////////////////////

    void Image::onAppend(const SharedNode &node)
    {
        if (node != m_image)
        {
            throw InvalidOperationException("Image not support child changes");
        }
        FrameLayout::onAppend(node);
    }

    void Image::onRemove(const SharedNode &node)
    {
        throw InvalidOperationException("Image not support child changes");
    }

}