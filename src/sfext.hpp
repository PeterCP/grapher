#pragma once

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace sf
{
	class SFML_GRAPHICS_API LineShape : public Shape
	{
    public:
		explicit LineShape(const Vector2f & start = {}, const Vector2f & finish = {},
                           float thickness = 3.f);

		void setThickness(float thickness);

		float getThickness() const;

        void setStart(const Vector2f & start);

        Vector2f getStart() const;

        void setFinish(const Vector2f & finish);

        Vector2f getFinish() const;

        Vector2f getDirection() const;

		float getLength() const;

		virtual std::size_t getPointCount() const;

		virtual Vector2f getPoint(std::size_t index) const;

    private:
        Vector2f m_start, m_finish; ///< Direction of the line
        float m_thickness;    ///< Thickness of the line
    };

}
