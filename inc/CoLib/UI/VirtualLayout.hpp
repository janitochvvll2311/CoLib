#ifndef COLIB_VIRTUAL_LAYOUT_HPP
#define COLIB_VIRTUAL_LAYOUT_HPP

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <CoLib/Graphics/Graph.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API VirtualLayout
        : public FrameLayout
    {

    public:
        const sf::Transform &getInnerTransform() const;
        void setInnerTransform(const sf::Transform &value);

        ///////////////////////////////////////////////////////////////////////////

        void compact() override;

        sf::Vector2f getInnerPoint(const sf::Vector2f &point) const override;

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable sf::RenderTexture m_texture;
        mutable Graph m_surface;
        sf::Transform m_transform;
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP