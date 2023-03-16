#ifndef COLIB_IMAGE_HPP
#define COLIB_IMAGE_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API Image : public FrameLayout
    {

    public:
        Anchor getHorizontalContentAnchor() const;
        void setHorizontalContentAnchor(Anchor value);

        Anchor getVerticalContentAlignment() const;
        void setVerticalContentAnchor(Anchor value);

        const SharedBackground &getImage() const;

        Image();
        virtual ~Image();

    protected:
        void onAppend(const SharedNode &node) override;
        void onRemove(const SharedNode &node) override;

    private:
        SharedBackground m_image;
    };

}

#endif // COLIB_IMAGE_HPP