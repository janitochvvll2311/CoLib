#ifndef COLIB_RECTGEO_HPP
#define COLIB_RECTGEO_HPP

#include <CoLib/Graphics/Export.hpp>
#include <CoLib/Graphics/Geometry.hpp>

namespace co
{

    class COLIB_GRAPHICS_API RectGeo : public Geometry
    {

    public:
        szt getPointCount() const override;
        sf::Vector2f getPoint(szt index, szt precision = 1) const override;
        bool contains(const sf::Vector2f &point) const override;

        RectGeo(const sf::FloatRect &rect);
        RectGeo(const sf::Vector2f &size);

    private:
        sf::Vector2f m_start;
        sf::Vector2f m_end;
        sf::Vector2f m_size;
    };

}

#endif // COLIB_RECTGEO_HPP