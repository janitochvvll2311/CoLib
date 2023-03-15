#ifndef COLIB_LABEL_HPP
#define COLIB_LABEL_HPP

#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class Span;
    using SharedSpan = std::shared_ptr<Span>;

    ///////////////////////////////////////////////////////

    class COLIB_UI_API Label : public FrameLayout
    {

    public:
        Anchor getHorizontalContentAnchor() const;
        void setHorizontalContentAlignment(Anchor value);

        Anchor getVerticalContentAlignment() const;
        void setVerticalContentAnchor(Anchor value);

        const SharedSpan &getSpan() const;

        Label();
        virtual ~Label();

    protected:
        void onAttach(const SharedWidget &widget) override;
        void onDetach(const SharedWidget &widget) override;

    private:
        SharedSpan m_span;
    };

}

#endif // COLIB_LABEL_HPP