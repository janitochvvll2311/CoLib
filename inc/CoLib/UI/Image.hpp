#ifndef COLIB_IMAGE_HPP
#define COLIB_IMAGE_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API Image : public FrameLayout
    {

    public:
        Anchor getHorizontalContentAnchor() const;
        void setHorizontalContentAlignment(Anchor value);

        Anchor getVerticalContentAlignment() const;
        void setVerticalContentAnchor(Anchor value);

        const SharedBackground &getImage() const;

        Image();
        virtual ~Image();

    protected:
        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        SharedBackground m_image;
    };

}

#endif // COLIB_IMAGE_HPP