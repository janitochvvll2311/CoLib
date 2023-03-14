#ifndef COLIB_VIRTUAL_LAYOUT_HPP
#define COLIB_VIRTUAL_LAYOUT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API VirtualLayout
        : public FrameLayout
    {

    public:
        void compact() override;

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable sf::RenderTexture m_texture;
        mutable Graph m_surface;
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP