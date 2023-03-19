#ifndef COLIB_ELLIPSE_HPP
#define COLIB_ELLIPSE_HPP

#include <CoLib/Graphics/Geometry.hpp>

namespace co
{

    class COLIB_GRAPHICS_API Ellipse
        : public virtual Geometry
    {

    public:
        std::size_t getPointCount() const override;
        sf::Vector2f getPoint(std::size_t index, std::size_t precision = 1) const override;
        bool contains(const sf::Vector2f &point) const override;

        Ellipse(f32t radiusX, f32t radiusY);
        Ellipse(f32t centerX, f32t centerY, f32t radiusX, f32t radiusY);
        ~Ellipse();

    private:
        f32t m_centerX;
        f32t m_centerY;
        f32t m_radiusX;
        f32t m_radiusY;
        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

} // co

#endif // COLIB_ELLIPSE_HPP