#include "sfext.hpp"
#include <cmath>

namespace sf
{

    LineShape::LineShape(const Vector2f & start, const Vector2f & finish,
                         float thickness)
        : m_start(start)
        , m_finish(finish)
        , m_thickness(thickness)
    {
        setPosition(m_start);
        update();
    }

    void LineShape::setThickness(float thickness)
    {
        m_thickness = thickness;
        update();
    }

    float LineShape::getThickness() const
    {
        return m_thickness;
    }

    void LineShape::setStart(const Vector2f & start)
    {
        m_start = start;
        setPosition(m_start);
        update();
    }

    Vector2f LineShape::getStart() const
    {
        return m_start;
    }

    void LineShape::setFinish(const Vector2f & finish)
    {
        m_finish = finish;
        update();
    }

    Vector2f LineShape::getFinish() const
    {
        return m_finish;
    }

    Vector2f LineShape::getDirection() const
    {
        return m_finish - m_start;
    }


    float LineShape::getLength() const
    {
        Vector2f d = getDirection();
        return std::sqrt(d.x * d.x + d.y * d.y);
    }


    std::size_t LineShape::getPointCount() const
    {
        return 4;
    }


    Vector2f LineShape::getPoint(std::size_t index) const
    {
        Vector2f direction = getDirection();
        Vector2f unitDirection = direction / getLength();
        Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

        Vector2f offset = (m_thickness/2.f)*unitPerpendicular;

        switch (index)
        {
            default:
            case 0: return offset;
            case 1: return (direction + offset);
            case 2: return (direction - offset);
            case 3: return (-offset);
        }
    }

}
