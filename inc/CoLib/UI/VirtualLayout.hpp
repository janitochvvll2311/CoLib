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

        bool dispatchChildrenEvents(Node *target, const sf::Event &event) const override;
        sf::Vector2f getInnerPoint(const sf::Vector2f &point) const;

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        sf::Vector2f compactContent() const override final;
        void placeContent(const sf::Vector2f &origin) const override final;
        void updateContent() const override final;
        void drawContent(sf::RenderTarget &target, const sf::RenderStates &states) const override final;

    private:
        mutable sf::RenderTexture m_texture;
        mutable sf::VertexArray m_surface;
        sf::Transform m_transform;
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP