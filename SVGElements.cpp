#include "SVGElements.hpp"

namespace svg
{
    // These must be defined!
    SVGElement::SVGElement() {}
    SVGElement::~SVGElement() {}
    

    Ellipse::Ellipse(const Color &fill, const Point &center, const Point &radius)
        : fill(fill), center(center), radius(radius)
    {
    }
    Point Ellipse::transform(const std::string &t_name, const Point &origin, int mul = 0) const
        if(t_name == "translate"){
            return center.translate(origin);
        }
    Point Ellipse::rotate(const std::string &t_name, const Point &origin, int radius) const{
        if(t_name == "rotate"){
            return center.rotate(origin);
    }
    Point Ellipse::scale(const std::string &t_name, const Point &origin, int mul = 0, const int &val){
        if(t_name == "scale"){
            return center.scale(origin);
        }
    }

    void Ellipse::draw(PNGImage &img, transform) const
    {
    }



    }





    Polyline::Polyline(const Color &stroke, const std::vector<Point>& points)
        : stroke(stroke), points(points)
    {
    }

    void PolyLine::draw(PNGImage &img) const
    {
        img.draw_PolyLine(, stroke);
    }

    Polygon::Polygon(const Color &fill, const std::vector<Point>& points)
        : fill(fill), points(points)
    {
    }

    void Polygon::draw(PNGImage &img) const
    {
        img.draw_Polygon(points, fill);
    }

    Point Polygon::transform(const std::string &t_name, const std::vector<Point>& points, int mul = 0) const
    if(t_name == "translate"){
        



}
}
