#ifndef COLIB_RECTANGLE_HPP
#define COLIB_RECTANGLE_HPP

#include <CoLib/Graphics/Export.hpp>
#include <CoLib/Graphics/Geometry.hpp>

namespace co
{

    class COLIB_GRAPHICS_API Rectangle : public Geometry
    {

    public:
        std::size_t getPointCount() const override;
        sf::Vector2f getPoint(std::size_t index, std::size_t precision = 1) const override;
        bool contains(const sf::Vector2f &point) const override;

        Rectangle(f32t width, f32t height);
        Rectangle(f32t left, f32t top, f32t width, f32t height);
        ~Rectangle();

    private:
        f32t m_left;
        f32t m_top;
        f32t m_width;
        f32t m_height;
        f32t m_rigth;
        f32t m_bottom;
    };

} // co

#endif // COLIB_RECTANGLE_HPP