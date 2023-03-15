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
        void setInnterTransform(const sf::Transform &value);

        ///////////////////////////////////

        VirtualLayout();
        virtual ~VirtualLayout();

    protected:
        sf::Vector2f getContentSize() const override;
        bool dispatchInnerEvent(const SharedWidget &widget, Widget *target, const sf::Event &event) const override;

        void onDraw(sf::RenderTarget &target, const sf::RenderStates &states) const override;
        void onUpdate() const override;

    private:
        mutable sf::RenderTexture m_texture;
        mutable Graph m_surface;
        sf::Transform m_transform;
    };

}

#endif // COLIB_VIRTUAL_LAYOUT_HPP