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
        void setHorizontalContentAnchor(Anchor value);

        Anchor getVerticalContentAlignment() const;
        void setVerticalContentAnchor(Anchor value);

        const SharedSpan &getSpan() const;

        Label();
        virtual ~Label();

    protected:
        void onAppend(const SharedNode &node) override;
        void onRemove(const SharedNode &node) override;

    private:
        SharedSpan m_span;
    };

}

#endif // COLIB_LABEL_HPP