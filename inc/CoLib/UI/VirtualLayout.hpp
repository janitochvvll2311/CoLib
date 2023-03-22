#ifndef COLIB_VIRTUAL_LAYOUT_HPP
#define COLIB_VIRTUAL_LAYOUT_HPP

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <CoLib/UI/FrameLayout.hpp>

namespace co
{

    class COLIB_UI_API VirtualLayout
        : public FrameLayout
    {

    public:
        const sf::Transform &getInnerTransform() const;
        void setInnerTransform(const sf::Transform &value);

        sf::Vector2f getInnerPoint(const sf::Vector2f &point) const override final;

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

        sf::Vector2f compactContent() const override final;
        void updateContent() const override final;

    private:
        mutable sf::RenderTexture m_texture;
        mutable sf::VertexArray m_surface;
        sf::Transform m_transform;
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP