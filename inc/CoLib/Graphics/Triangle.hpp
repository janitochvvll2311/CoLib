#ifndef COLIB_TRIANGLE_HPP
#define COLIB_TRIANGLE_HPP

#include <CoLib/Graphics/Geometry.hpp>

namespace co
{

    class COLIB_GRAPHICS_API Triangle : public virtual Geometry
    {

    public:
        std::size_t getPointCount() const override;
        sf::Vector2f getPoint(std::size_t index, std::size_t precision = 1) const override;
        bool contains(const sf::Vector2f &point) const override;

        Triangle(const sf::Vector2f &pointA, const sf::Vector2f &pointB, const sf::Vector2f &pointC);
        ~Triangle();

    private:
        sf::Vector2f m_pointA;
        sf::Vector2f m_pointB;
        sf::Vector2f m_pointC;
        f32t m_left;
        f32t m_top;
        f32t m_right;
        f32t m_bottom;
    };

} // co

#endif // COLIB_TRIANGLE_HPP