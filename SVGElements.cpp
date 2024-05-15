#include "SVGElements.hpp"
#include "Point.hpp"
#include "Color.hpp"
#include "PNGImage.hpp"


namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}

    // Ellipse (initial code provided)
    Ellipse::Ellipse(const Color &fill,
                     const Point &center,
                     const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center, radius, fill);
    }

    // Circle class
   Circle::Circle(float cx, float cy, float radius, const Color &fillColor)
    : Ellipse(fillColor, Point(static_cast<int>(cx), static_cast<int>(cy)), Point(static_cast<int>(radius), static_cast<int>(radius))) {
    }

    void Circle::draw(PNGImage& img) const {
        img.draw_ellipse(center, radius, fill);
    }

    // Line
    Line::Line(const Point& start, const Point& end, const Color& strokeColor)
        : start(start), end(end), strokeColor(strokeColor) {}

    void Line::draw(PNGImage& img) const {
        img.draw_line(start, end, strokeColor);
    }

    // Polyline
    Polyline::Polyline(const std::vector<Point>& points, const Color& strokeColor)
            : Line(points.front(), points.back(), strokeColor), points(points) {}

    void Polyline::draw(PNGImage& img) const {
        for (size_t i = 0; i < points.size() - 1; ++i) {
            img.draw_line(points[i], points[i + 1], strokeColor);
        }
    }


    // Polygon
    Polygon::Polygon(const std::vector<Point>& points, const Color& fillColor)
        : points(points), fillColor(fillColor) {}

    void Polygon::draw(PNGImage& img) const {
        img.draw_polygon(points, fillColor);
    }
    


    Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight, const Color& fillColor)
        : Polygon({
            topLeft,
            Point(bottomRight.x, topLeft.y),
            bottomRight,
            Point(topLeft.x, bottomRight.y)
        }, fillColor) {}

    void Rectangle::draw(PNGImage& img) const {
        img.draw_polygon(points, fillColor);
    }


    void Group::addElement(SVGElement* element) {
        elements.push_back(element);
    }

    void Group::draw(PNGImage& img) const {
        for (const auto& element : elements) {
            element->draw(img);
        }
    }
}