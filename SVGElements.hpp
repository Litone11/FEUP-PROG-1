//! @file shape.hpp
#ifndef _svg_SVGElements_hpp_
#define _svg_SVGElements_hpp_

#include "Color.hpp"
#include "Point.hpp"
#include "PNGImage.hpp"
#include <vector>
#include <string>

namespace svg
{
    class SVGElement
    {

    public:
        SVGElement();
        virtual ~SVGElement();
        virtual void draw(PNGImage &img) const = 0;
    };

    // Declaration of namespace functions
    // readSVG -> implement it in readSVG.cpp
    // convert -> already given (DO NOT CHANGE) in convert.cpp

    void readSVG(const std::string &svg_file,
                 Point &dimensions,
                 std::vector<SVGElement *> &svg_elements);
    void convert(const std::string &svg_file,
                 const std::string &png_file);


    // ELLIPSE CLASS
    class Ellipse : public SVGElement {
    public:
        Ellipse(const Color &fill, const Point &center, const Point &radius);
        void draw(PNGImage &img) const override;


    protected:
    const Point& getCenter() const { return center; }
    const Point& getRadius() const { return radius; }
    Color fill;
    Point center;
    Point radius;

    };

    // CIRCLE CLASS
    class Circle : public Ellipse {
        public:
            Circle(float cx, float cy, float radius, const Color &fillColor);
            void draw(PNGImage &img) const override;
    };


    // LINE CLASS
    class Line : public SVGElement {
    public:
        Line(const Point& start, const Point& end, const Color& strokeColor);
        void draw(PNGImage& img) const override;

    protected:
        Point start;
        Point end;
        Color strokeColor;
    };

    class Polyline : public Line {
    private:
        std::vector<Point> points;        
        public:
        Polyline(const std::vector<Point>& points, const Color& strokeColor);
        void draw(PNGImage& img) const override;
    };
    // POLYGONE CLASS
    class Polygon : public SVGElement {
    public:
        Polygon(const std::vector<Point>& points, const Color& fillColor);
        void draw(PNGImage& img) const override;
    
    protected:
        std::vector<Point> points;
        Color fillColor;
    };

    // RECTANGLE CLASS
    class Rectangle : public Polygon {
    public:
        Rectangle(const Point& topLeft, const Point& bottomRight, const Color& fillColor);
        void draw(PNGImage& img) const override;
    };


    // GROUP CLASS
    class Group : public SVGElement {
    public:
        void addElement(SVGElement* element);
        void draw(PNGImage& img) const override;

    private:
        std::vector<SVGElement*> elements;
    };


}
#endif