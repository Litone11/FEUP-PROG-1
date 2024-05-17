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
    Point Ellipse::transform(const std::string &t_name, const Point &origin, int &mul = NULL) const
        if(t_name == "translate"){
            return center.translate(origin);
        }
    
        else if(t_name == "rotate"){
            return center.rotate(origin, mul);
    
        }
        else if(t_name == "scale"){
            return center.scale(origin, mul);
        }
    }

    void Ellipse::draw(PNGImage &img) const
    {
        img.draw_ellipse(center,radius,fill);
    }









    Polyline::Polyline(const Color &stroke, const std::vector<Point>& points)
        : stroke(stroke), points(points)
    {
    }



    std::vector<Point> Polyline::transform(const std::string &t_name, const std::vector<Point>& points, int &mul = NULL) const

   
    if(t_name == "translate"){
        std::vector<Point> new_points;
        for(auto p : points){
            new_points.push_back(p.translate(origin));
            }
    return new_points;

    else if (t_name == "rotate"){
        std::vector<Point> new_points;
        for(auto p : points){
            new_points.push_back(p.rotate(origin, mul));
            
            } 
        return new_points; 

    else if(t_name == "scale"){
        std::vector<Point> new_points;
        for(auto p : points){
            new_points.push_back(p.scale(origin, mul));
            }
        return new_points;
    }
    }


    void PolyLine::draw(PNGImage &img) const
    {
        for(int i = 0; i< points.size() - 1; i++)
            img.draw_line(points.at(i), points.at(i+1), stroke);
    }







    Polygon::Polygon(const Color &fill, const std::vector<Point>& points)
        : fill(fill), points(points)
    {
    }

    std::vector<Point> Polygon::transform(const std::string &t_name, const std::vector<Point>& points, int mul = 0) const{
    if(t_name == "translate"){
        std::vector<Point> new_points;
        
        
        for(auto p : points){
            new_points.push_back(p.translate(origin));
        }
        return new_points;
    }


        else if(t_name == "rotate"){
        std::vector<Point> new_points;
        for(auto p : points){
            new_points.push_back(p.rotate(origin));
        }
        return new_points;
    }


        else if(t_name == "scale"){
        std::vector<Point> new_points;
        for(auto p : points){
            new_points.push_back(p.scale(origin));
        }
        return new_points;
    }
    }


        void Polygon::draw(PNGImage &img) const
    {
        if(new_points == NULL){
            img.draw_polygon(points, fill);
        }
        else{
            img.draw_polygon(new_points, fill);
        }
    }



}

