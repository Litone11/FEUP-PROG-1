#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}



    //Circle code
    Circle::Circle(const Color &fill,
                    const Point &center,
                    const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }

    void Cicle::draw(PNGImage &img) const
    {
        img.draw_Circle(center, radius, fill);
    }



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



    // define a corresponding class in SVGElements.hpp / SVGElements.cpp

    PolyLine::PolyLine(const Color &stroke,
    //points: a comma-separated sequence of XY coordinates;
    )
    {
    }

    //polyline void funct
    void PolyLine::draw(PNGImage &img) const
    {
        img.draw_PolyLine(, stroke);
    }


    Line::Line(const Color &stroke,
                const Point &start,
                const Point &end
                )
                :stroke(stroke), start(start), end(end)
    void Line::draw(PNGImage &img) const
    {
        img.draw_Line(start, end, stroke);
    }



    //line void funct

    Polygon::Polygon(const Color &fill,

    )

    //polygon void funct


    Rect::Rect(

    )

    //rect void function




}
